// 302.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <map>
#include <cpr/cpr.h>

int main() {
    setlocale(0, "");
    std::map<std::string, std::string> arguments;
    std::string key, value;

    
    while (true) {
        std::cout << "Введите название аргумента (или 'post'/'get' для завершения ввода): ";
        std::cin >> key;

        
        if (key == "post" || key == "get") {
            break;
        }

        std::cout << "Введите значение аргумента: ";
        std::cin >> value;

        arguments[key] = value; 
    }

   
    if (key == "post") {
       
        cpr::Parameters payload;
        for (const auto& arg : arguments) {
            payload.Add({ arg.first, arg.second });
        }

      
        cpr::Response r = cpr::Post(cpr::Url{ "https://httpbin.org/post" }, payload);

      
        std::cout << "Ответ сервера (POST): \n" << r.text << std::endl;

    }
    else if (key == "get") {
       
        std::string query_params = "?";
        for (const auto& arg : arguments) {
            query_params += arg.first + "=" + arg.second + "&";
        }
        if (!arguments.empty()) {
            query_params.pop_back(); 
        }

      
        cpr::Response r = cpr::Get(cpr::Url{ "https://httpbin.org/get" + query_params });

        
        std::cout << "Ответ сервера (GET): \n" << r.text << std::endl;
    }

    return 0;
}