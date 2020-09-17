# WeatherAppUnreal
 Тестовое Задание Weather App  
 Unreal Engine 4.23.3  
 Visual Studio 2017.   
Выводит список городов с указанием температуры из SQLite базы данных  
Файл базы данных расположен каталоге Content/DataBase/database.sqlite3  
В качестве источника данных используется http://openweathermap.org/API  
Чтобы найти нужный город, нужно ввести его название на русском в верхнее текстовое поле и нажать "Найти". Чтобы добавить его в список и в sqlite-базу данных, нажать "Добавить"  
При нажатии на кнопку с именем города выводит более подробную информацию о погоде.  
Реализация содержит как множество Blueprints, так и C++ составляющие.  
Offline mode - кеширование ранее загруженных данных в базу данных SQLite3, отображает их в
случае отсутствия интернета и позволяет обновлять кнопкой возле кнопки города.  В отображаемых данных в самом низу пометка, на какую дату и
время данные были получены и актуальны.  

