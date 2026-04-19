#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>
#include <httplib.h>
// ВАША ИСХОДНАЯ ЛОГИКА БЕЗ ИЗМЕНЕНИЙ
std::string process_text(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) words.push_back(word);
    if (words.empty()) return "";
    int sumlens = 0;
    for (size_t i = 0; i < words.size(); i++) sumlens += words[i].length();
    sumlens = sumlens / words.size();
    for (size_t i = 0; i < words.size(); i++) {
        if (words[i].size() <= (size_t)sumlens) {
            words.erase(words.begin() + i); i--;
        }
    }
    std::string result = "";
    for (size_t i = 0; i < words.size(); i++) result += words[i] + " ";
    return result;
}
// Счетчик запросов (атомарный, для потокобезопасности)
std::atomic<int> request_count{0};
int main() {
    // 1. Сервер МЕТРИК (Порт 8081)
    httplib::Server metrics_svr;
    metrics_svr.Get("/metrics", [](const httplib::Request&, httplib::Response& res) {
        // Формируем правильный текстовый формат Prometheus
        std::string body = "# HELP http_requests_total Total number of HTTP requests\n"
                           "# TYPE http_requests_total counter\n"
                           "http_requests_total " + std::to_string(request_count.load()) + "\n";
        
        res.set_content(body, "text/plain; version=0.0.4; charset=utf-8");
    });
    // Запускаем сервер метрик в отдельном потоке
    std::thread metrics_thread([&]() {
        metrics_svr.listen("0.0.0.0", 8081);
    });
    // 2. Сервер ПРИЛОЖЕНИЯ (Порт 8080)
    httplib::Server app_svr;
    app_svr.Post
("/process", [](const httplib::Request&, httplib::Response& res) {
        request_count++;
        std::string input = "тест тестирование длинноеслово программирование";
        res.set_content(process_text(input), "text/plain");
    });
    // Нагрузка для HPA
    app_svr.Get("/load", [](const httplib::Request&, httplib::Response& res) {
        request_count++;
        volatile double x = 0.0;
        for(int i=0; i<100000000; i++) x += i;
        res.set_content("CPU load generated", "text/plain");
    });
    std::cout << "App started on port 8080, Metrics on port 8081" << std::endl;
    app_svr.listen("0.0.0.0", 8080); // Главный поток блокируется здесь
    return 0;
}
