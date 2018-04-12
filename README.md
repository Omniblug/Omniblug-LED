Omniblug-LED
============

![Alt text](http://www.omniblug.com/img/blog/omniblug-led/opciones.jpg "Omniblug Bluetooth")

Remote Control LED RGB Bluetooth

http://www.omniblug.com

Construye tu propio proyecto arduino de domótica donde podrás controlar la temperatura y humedad gracias al sensor de temperatura DHT-11, también podrás controlar la iluminación gracias a las tiras LED RGB y manejar varios dispositivos de forma inalámbrica mediante el módulo bluetooth JY-MCU desde tu propio teléfono móvil.

1. Podrás conocer la temperatura y humedad.
2. Dispondrás de 2 controles de iluminación LED RGB independientes con control de intensidad.
3. Control de 4 swicht para distintos dispositivos.


Vídeo demostrativo: http://www.youtube.com/embed/5Nvw37oxIdw


Material necesario
==================

1. Arduino (Uno, Mega o Nano)
2. Módulo bluetooth JY-MCU (hc05 / hc06)
3. Array de transistores ULN2003A
4. Tiras de led 5050 RGB Ánodo Común
5. Sensor DHT-11 - Temperature / Humidity
6. Module Relay 5v 4 chanels
5. Alimentación led 12v
6. Software: Arduino
7. APP Omniblug (https://play.google.com/store/apps/details?id=com.omniblug)

Puedes ver el circuito de conexionado aqui (http://www.omniblug.com/img/blog/omniblug-led/omniblug-esquema.jpg)


Utilización
===========

Una vez cargado el scket, tenéis que esperar sobre unos 10 segundos ya que de inicio se programa el módulo bluetooth para su primer uso. 

El fin del proceso de programado del bluetooth ha terminado cuando los led del canal 1 cambien de color Rojo a color Verde.

Una vez que vemos los led de color verde hemos terminado con la configuración de nuestra unidad de control y ya la tendremos disponible para su uso.

El paso anterior solo será así si es la primera vez montáis el proyecto, si es una actualización a la V2 este paso no se ejecutará.

Por último nos queda instalar la aplicación Omniblug en nuestro dispositivo Android.

Accedemos a Google Play y la instalamos.

Una vez que abrimos la aplicación se nos pedirá conectar con nuestro dispositivo bluetooth, realizamos un escaneo y elegimos Omniblug para conectarnos.

Pin por defecto "1234".
