

build:
	platformio run

upload:
	platformio run --target upload

uploadOTA:
	#esptool.py --chip esp8266 --port 192.168.1.128 --baud 115200 -cp 192.168.1.128 -ca 0x00000 -cf ./.pio/build/esp_wroom_02/firmware.bin
	python3 espota.py -i 192.168.1.128 -p 8266 --auth= -f ./.pio/build/esp_wroom_02/firmware.bin
	
monitor:
	platformio device monitor --baud 115200
