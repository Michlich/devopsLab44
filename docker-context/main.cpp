#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <httplib.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/counter.h>
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
int main() {
    // Настройка Prometheus (порт 8081)
    prometheus::Exposer exposer{"0.0.0.0:8081
"};
    auto registry = std::make_shared<prometheus::Registry>();
    exposer.RegisterCollectable(registry);
    auto& http_requests_total = prometheus::BuildCounter()
        .Name("http_requests_total")
        .Help("Number of HTTP requests")
        .Register(*registry);
    auto& request_counter = http_requests_total.Add({{"endpoint", "/process"}});
    // HTTP сервер приложения (порт 8080)
    httplib::Server svr;
    svr.Post
("/process", [&request_counter](const httplib::Request&, httplib::Response& res) {
        request_counter.Increment();
        std::string input = "тест тестирование длинноеслово программирование";
        res.set_content(process_text(input), "text/plain");
    });
    // Эндпоинт для создания нагрузки на CPU (для теста HPA)
    svr.Get("/load", [&request_counter](const httplib::Request&, httplib::Response& res) {
        request_counter.Increment();
        volatile double x = 0.0;
        for(int i=0; i<100000000; i++) x += i;
        res.set_content("CPU load generated", "text/plain");
    });
    std::cout << "Server started on port 8080, Metrics on port 8081" << std::endl;
    svr.listen("0.0.0.0
", 8080);
    return 0;
}
