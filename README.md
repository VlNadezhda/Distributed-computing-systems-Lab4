# Distributed-computing-systems-Lab4

Постановка задачи:

Создать клиента с двумя потоками и север с двумя потоками.       
У каждого потока сервера свой файл( sync.txt и asyn.txt).       
Первый поток: сервер присылает информацию из sync.txt, когда пользователь что-то ввел.        
Второй поток: сервер отправляет данные раз в n секунд,        
клиент сравнивает с предыдущими данными от сервера и сообщает совпадают они или нет.       
