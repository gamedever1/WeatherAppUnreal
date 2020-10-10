# WeatherAppUnreal
 Приложение на UnrealEngine4 для получения данных о погоде, через **REST-API** сервиса http://openweathermap.org/API  
 Для запуска и компиляции использовалось:  
**Unreal Engine 4.23.3**  
**Visual Studio 2017.**   
 
 Готовую packaged игру-приложение можно скачать здесь - https://drive.google.com/file/d/1gLuCWudvHEW3K1VvsI05qWC2veX5Fxwh/view?usp=sharing
 
Программа выводит список городов с указанием температуры.
Добавленные в список города кешируются в базе данных в файле Content/DataBase/database.sqlite3  
Сначала нужно "Найти" нужный город, введя его название на русском в верхнее текстовое поле. Потом можно "Добавить" его в список и в sqlite-базу данных. При нажатии на кнопку с именем города выводит более подробную информацию о погоде. При нажатии на иконку обновления справа на кнопке города - обновляет данные.  
Сделано с использованием как **C++ классов**, так и **Blueprints**.

## **Главное окно программы:**
![2020-10-10_045537255](https://user-images.githubusercontent.com/55281328/95640618-02f78180-0ab7-11eb-8b5c-51b10c75ef10.jpg)

## **Блупринты:**
![2020-10-10_045647241](https://user-images.githubusercontent.com/55281328/95640805-00495c00-0ab8-11eb-9a70-4f029be633bb.png)
![2020-10-10_045721977](https://user-images.githubusercontent.com/55281328/95640823-135c2c00-0ab8-11eb-8a0d-22f26eaa27e5.png)
![2020-10-10_045737789](https://user-images.githubusercontent.com/55281328/95640824-1525ef80-0ab8-11eb-9b39-d4ae7a6a5a8d.png)

