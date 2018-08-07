// tests go here; this will not be compiled when this package is used as a library
MicroCar.RGB_Car_Big2(255)  
basic.forever(() => {
            
        MicroCar.RGB_Car_Program().setBrightness(1)
        MicroCar.RGB_Car_Program().setPixelColor(1, neopixel.colors(NeoPixelColors.Green))
        MicroCar.RGB_Car_Program().show()    
})
MicroCar.initIR()

MicroCar.onPressEvent(0x00, () => {
        basic.showNumber(1)
        basic.showNumber(2)
})


