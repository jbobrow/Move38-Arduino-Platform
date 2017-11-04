/*
 * Access the service port 
 *
 * The service port has a high speed (500Kbps) bi-directional serial connection plus an Aux pin that can be used
 * as either digitalIO or an analog in. 
 *
 * Mostly useful for debugging, but maybe other stuff to? :)
 * 
 */ 


#ifndef SP_H_

    #define SP_H_
    
    #include "blinkcore.h"    
    
    #include "hardware.h"

    #include "utils.h"          // Grab SBI and CBI

    #include <util/delay.h>     // Pull in _delay_us() for pulse functions
    
    #ifndef SP_PRESENT                   // Is service port present on this variant?
    
        #error This board variant does not have a serivce port!
    
    #endif

    // Set the pin direction for the service port aux (A) pin

    #define SP_AUX_MODE_OUT()       SBI( SP_AUX_DDR , SP_AUX_PIN )
    #define SP_AUX_MODE_IN()        CBI( SP_AUX_DDR , SP_AUX_PIN )

    // Set the level on the service port aux (A) pin. 
    // These execute in a single instruction
    // You must set the aux pin to output mode first or else 
    // driving 1 will just enable the pullup. 

    #define SP_AUX_1()               SBI( SP_AUX_PORT, SP_AUX_PIN)
    #define SP_AUX_0()               CBI( SP_AUX_PORT, SP_AUX_PIN)
        
    // Initialize the service port for a serial connection on pins T and R. 
        
    void sp_serial_init(void);
                
    // Send a byte out the serial port. Blocks if a transmit already in progress. 
    // Must call sp_serial_init() first
        
    void sp_serial_tx(byte b);
        
    #define DEBUG_SERIAL_TX_NOW(b) (SP_SERIAL_DATA_REG=b)      // Send blindly, but instantly (1 instruction)  Could clobber, but you'd have to send pretty darn fast for that.
        
    // Is there a char ready to read?

    uint8_t sp_serial_rx_ready(void);

    // Read byte from service port serial. Blocks if nothing received yet.

    uint8_t sp_serial_rx(void);        
                
    // Read the analog voltage on service port pin A
    // Returns 0-255 for voltage between 0 and Vcc
    // Handy to connect a potentiometer here and use to tune params
    // like rightness or speed
        
    // You should call SP_AUX_MODE_IN() first or else this will be very boring
    // You also probably want to call SP_AUX_0() first or else the pull-up on this pin will be active

    uint8_t sp_aux_analogRead(void);
        
#endif /* DEBUG_H_ */