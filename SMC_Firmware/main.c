#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"


#define MCU_CLK 200 //Set clock to 200Mhz
#define I2C_BAUDRATE 2000 //Set in terms of Kb/s
#define FPGA0_CLK_CYCLE 1 //Set the PWM cycle speed to 2 cycles. Frequency = MCU CLK / Cycle + 1  --> 200/2 = 100Mhz
#define FPGA1_CLK_CYCLE 1
#define REV "1.5b" //Firmware Revision. Update when changed

//USER IO Definitions
const uint LED_PIN = 25; //GPIO 25
const uint BUTTON_PIN = 20; //GPIO 20
const uint FPGA0_SPI_CLK = 18; //FPGA SPI CLK can be used as system clock as well. Must choose between SPI and SYS_CLK function!!!
const uint FPGA1_SPI_CLK = 14;

//PMU CTRL Definitions
const uint PMU_MODE = 6; 
const uint PMU_EN_CH1 = 8; 
const uint PMU_EN_CH2 = 10;
const uint PMU_EN_CH3 = 9;
const uint PMU_EN_CH4 = 7; 
const uint PMU_PGOOD = 14;
const uint PMU_TEMP = 26;

//PWR MON Definitions
const uint PWR_MON_ADDR[4] = {0x40, 0x41, 0x42, 0x43};

void initIO(){
        /*TODO: Add defines for Display module and FPGA IO Pins

    */

    sleep_ms(250);
    printf("Initialzing IO...\n");
    sleep_ms(250);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(PMU_MODE);
    gpio_set_dir(PMU_MODE, GPIO_OUT);
    gpio_init(PMU_EN_CH1);
    gpio_set_dir(PMU_EN_CH1, GPIO_OUT);
    gpio_init(PMU_EN_CH2);
    gpio_set_dir(PMU_EN_CH2, GPIO_OUT);
    gpio_init(PMU_EN_CH3);
    gpio_set_dir(PMU_EN_CH3, GPIO_OUT);
    gpio_init(PMU_EN_CH4);
    gpio_set_dir(PMU_EN_CH4, GPIO_OUT);
    gpio_init(PMU_PGOOD);
    gpio_set_dir(PMU_PGOOD, GPIO_IN);


    gpio_set_function(FPGA0_SPI_CLK, GPIO_FUNC_PWM);
    uint slice_num_0 = pwm_gpio_to_slice_num(FPGA0_SPI_CLK);
    // Set period
    pwm_set_wrap(slice_num_0, FPGA0_CLK_CYCLE);
    // Set channel A output for 50% duty cycle
    pwm_set_chan_level(slice_num_0, PWM_CHAN_A, ((FPGA0_CLK_CYCLE+1)/2));
    // Set the PWM running
    pwm_set_enabled(slice_num_0, true);

    gpio_set_function(FPGA1_SPI_CLK, GPIO_FUNC_PWM);
    uint slice_num_1 = pwm_gpio_to_slice_num(FPGA1_SPI_CLK);
    // Set period
    pwm_set_wrap(slice_num_1, FPGA1_CLK_CYCLE);
    // Set channel A output for 50% duty cycle
    pwm_set_chan_level(slice_num_1, PWM_CHAN_A, ((FPGA1_CLK_CYCLE+1)/2));
    // Set the PWM running
    pwm_set_enabled(slice_num_1, true);

    return; 
}

void blinkStatusLED(){
    for(int i = 0; i < 3; i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(150);
        gpio_put(LED_PIN, 0);
        sleep_ms(150);
    }
    return;
}

void initI2C(){
    uint8_t regbuf[2];
    uint8_t MFRID_PTR = 0xFE;
    uint8_t CFG_REG = 0x00;
    uint8_t CFG_DATA[3] = {0x00, 0xFF, 0xFF}; // Based on datasheet, send CFG ponter address first, then the two bytes of data

    i2c_init(i2c_default, I2C_BAUDRATE * 1000); // Using default I2C pins 4 and 5. Testing with 250Kb/s Bus speed, will increase later
    printf("Setting I2C to Default, %dKb/s\n", I2C_BAUDRATE);
    sleep_ms(150);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    printf("I2C initialzied as default. Reading INA260 MFR ID...\n");

    for(int i=0; i<(sizeof(PWR_MON_ADDR)/sizeof(PWR_MON_ADDR[0])); i++){
        i2c_write_blocking(i2c_default, PWR_MON_ADDR[i], &MFRID_PTR, 1, true); //Need to first address the register
        i2c_read_blocking(i2c_default, PWR_MON_ADDR[i], regbuf, 2, true); //Then read the data from register
        if (regbuf[0] == 0 && regbuf[1] == 0){
            printf("Error: Invalid response from Power monitor 0x%x. Please check chip and bus functionality.\n", PWR_MON_ADDR[i]);
            break;
        }
        else
        {
            printf("PWR MON 0x%x (CH%d) OK - MFR ID: 0x%x%x\n", PWR_MON_ADDR[i], i, regbuf[0], regbuf[1]);
            sleep_ms(250);
        }
    }

    printf("Configuring Power Monitor Registers...\n");
    for(int i=0; i<(sizeof(PWR_MON_ADDR)/sizeof(PWR_MON_ADDR[0])); i++){
        i2c_write_blocking(i2c_default, PWR_MON_ADDR[i], CFG_DATA, 3, true);
        i2c_read_blocking(i2c_default, PWR_MON_ADDR[i], regbuf, 2, true);

        if (regbuf[0] != CFG_DATA[0] || regbuf[1] != CFG_DATA[1]){
            printf("CH%d register data is: 0x%x%x\n", i, regbuf[0], regbuf[1]);
            printf("Warning: Power Monitor Configuration failed. Default Configuration Used.\n");
        }
        else
        {
            printf("CH%d configured.\n", i);
        }
        sleep_ms(250);
    }

    return;

}

void sysInit(){
    sleep_ms(250);
    printf("Initializing system...\n");
    sleep_ms(250);
    printf("Establishing I2C connection to Power Monitors...\n");
    sleep_ms(250);
    initI2C();
    blinkStatusLED();
}

void readPwrMon(float *voltage, float *current, float *power){
    uint8_t regbuf[2]; //Two Byte buffer to hold 16-bit Voltage/Current/Power readings from Power monitor
    const uint8_t CURRENT_REG = 0x01;
    const uint8_t VOLTAGE_REG = 0x02;
    const uint8_t POWER_REG = 0x03;

    const float VOLTAGE_SCALE = 0.00125;
    const float CURRENT_SCALE = 0.00125;
    const float POWER_SCALE = 0.01;

    uint16_t tempVoltage;
    uint16_t tempCurrentUnsigned;
    int16_t tempCurrentSigned;
    uint16_t tempPower;


    for(int i=0; i<(sizeof(PWR_MON_ADDR)/sizeof(PWR_MON_ADDR[0])); i++){
        i2c_write_blocking(i2c_default, PWR_MON_ADDR[i], &VOLTAGE_REG, 1, true);
        i2c_read_blocking(i2c_default, PWR_MON_ADDR[i], regbuf, 2, true);
        tempVoltage = (regbuf[0]<<8) | regbuf[1];
        voltage[i] = (float)((unsigned int)(tempVoltage)*VOLTAGE_SCALE);

        regbuf[0] = 0;
        regbuf[1] = 0;

        i2c_write_blocking(i2c_default, PWR_MON_ADDR[i], &CURRENT_REG, 1, true);
        i2c_read_blocking(i2c_default, PWR_MON_ADDR[i], regbuf, 2, true);
        tempCurrentUnsigned = ((regbuf[0]<<8)) | regbuf[1];
        tempCurrentSigned = (int16_t)tempCurrentUnsigned;
        if(tempCurrentSigned < 0){
            tempCurrentSigned = ~tempCurrentSigned + 1;
        }

        current[i] = (float)(tempCurrentSigned*CURRENT_SCALE);

        regbuf[0] = 0;
        regbuf[1] = 0;

        i2c_write_blocking(i2c_default, PWR_MON_ADDR[i], &POWER_REG, 1, true);
        i2c_read_blocking(i2c_default, PWR_MON_ADDR[i], regbuf, 2, true);
        tempPower = (regbuf[0]<<8) | regbuf[1];
        power[i] = (float)(tempPower*POWER_SCALE);

        regbuf[0] = 0;
        regbuf[1] = 0;
    }

    printf("\rVCCIO %0.3fV, %0.3fA, %0.3fW | VCCAUX %0.3fV, %0.3fA, %0.3fW | VCCMGT %0.3fV, %0.3fA, %0.3fW | VCORE %0.3fV, %0.3fA, %0.3fW",
           voltage[0], current[0], power[0], voltage[1], current[1], power[1], voltage[2], current[2], power[2], voltage[3], current[3], power[3]);
    fflush(stdout);
}

int main() {
    
    set_sys_clock_khz((MCU_CLK*1000), true); //Increase clock from 133Mhz to 220Mhz
    stdio_init_all(); 
    sleep_ms(1500);
    printf("\n");
    printf("SMC Firmware Rev: %s\n", REV);
    sleep_ms(250);
    printf("SMC CLK is: %dMhz\n", MCU_CLK);
    sleep_ms(250);
    printf("FPGA0 CLK is: %dMhz\n", (MCU_CLK/(FPGA0_CLK_CYCLE+1)));
    sleep_ms(250);
    printf("FPGA1 CLK is: %dMhz\n", (MCU_CLK/(FPGA1_CLK_CYCLE+1)));
    initIO();
    sleep_ms(250);
    printf("IO Initialization done!\n");
    sysInit();
    sleep_ms(250);
    printf("System Initialization done!\n");

    float current[4] = {0, 0, 0, 0};
    float voltage[4] = {0, 0, 0, 0};
    float power[4] = {0, 0, 0, 0};

    bool pressed;
    bool oldState;
    bool newState;

    while (true) {

        newState = gpio_get(BUTTON_PIN);
        if (oldState == 1 && newState == 0){
            if(pressed==0){
                //printf("Button Pressed\n");
                pressed = 1; 
                gpio_put(PMU_EN_CH1, 1);
                gpio_put(PMU_EN_CH2, 1);
                gpio_put(PMU_EN_CH3, 1);
                gpio_put(PMU_EN_CH4, 1);
                gpio_put(LED_PIN, 1);
            }
            else
            {
                gpio_put(LED_PIN, 0);
                gpio_put(PMU_EN_CH1, 0);
                gpio_put(PMU_EN_CH2, 0);
                gpio_put(PMU_EN_CH3, 0);
                gpio_put(PMU_EN_CH4, 0);
                pressed = 0;
            }
        }
        oldState = newState;
        readPwrMon(voltage, current, power);
        sleep_ms(100);
    }
}