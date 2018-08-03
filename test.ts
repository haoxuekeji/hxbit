// tests go here; this will not be compiled when this package is used as a library
hxbit_car.RGB_Car_Big(45, 45, 45)  
basic.forever(() => {
            
        hxbit_car.RGB_Car_Program().setBrightness(1)
        hxbit_car.RGB_Car_Program().setPixelColor(1, neopixel.colors(NeoPixelColors.Green))
        hxbit_car.RGB_Car_Program().show()    
})
