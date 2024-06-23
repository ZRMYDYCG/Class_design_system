#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

class Order {
private:
    char order_id[20];
    char company_name[50];
    char product_name[50];
    double product_price;
    int order_quantity;
    double order_amount;
public:
    /** 
     * 添加订单信息
     * @description 收集用户输入的订单信息，并计算订单金额。
     * @complexity 时间复杂度：O(1)，仅涉及基本的输入输出操作。
     */
    void add_order() {
        cout << "请输入订单编号：";
        cin >> order_id;
        cout << "请输入公司名称：";
        cin >> company_name;
        cout << "请输入产品名称：";
        cin >> product_name;
        cout << "请输入产品定价：";
        cin >> product_price;
        cout << "请输入订购数量：";
        cin >> order_quantity;
        order_amount = product_price * order_quantity;
        cout << "订单金额为：" << order_amount << endl;
    }

    /** 
     * 显示订单详情
     * @description 打印订单的所有详细信息。
     * @complexity 时间复杂度：O(1)，输出操作。
    */
    void display_order() {
        cout << "订单编号：" << order_id << endl;
        cout << "公司名称：" << company_name << endl;
        cout << "产品名称：" << product_name << endl;
        cout << "产品定价：" << product_price << endl;
        cout << "订购数量：" << order_quantity << endl;
        cout << "订单金额：" << order_amount << endl;
    }

    /** 
     * 获取订单编号
     * @return char* 返回订单编号的字符串。
     * @description 返回订单编号的指针。
     * @complexity 时间复杂度：O(1)。
    */
    char* get_order_id() {
        return order_id;
    }

    /** 
     * 获取公司名称
     * @return char* 返回公司名称的字符串。
     * @description 返回公司名称的指针。
     * @complexity 时间复杂度：O(1)。
    */
    char* get_company_name() {
        return company_name;
    }

    /** 
     * 获取订单金额
     * @return double 返回订单的总金额。
     * @description 返回计算后的订单金额。
     * @complexity 时间复杂度：O(1)。
    */
    double get_order_amount() {
        return order_amount;
    }

    /** 
     * 写入订单到文件
     * @description 将订单信息追加到文本文件orders.txt中。
     * @complexity 时间复杂度：O(1)，假设文件写入操作是常数时间。
    */
    void write_order() {
        ifstream fin("orders.txt");
        ofstream fout("temp.txt");
        bool found = false;
        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            string id, cname, pname;
            double price;
            int quantity;
            iss >> id >> cname >> pname >> price >> quantity;
            if (id == order_id && cname == company_name && pname == product_name) {
                found = true;
                quantity += order_quantity;
                fout << id << " " << cname << " " << pname << " " << price << " " << quantity << " " << price * quantity << endl;
            } else {
                fout << line << endl;
            }
        }
        fin.close();
        if (!found) {
            fout << order_id << " " << company_name << " " << product_name << " " << product_price << " " << order_quantity << " " << order_amount << endl;
        }
        fout.close();
        remove("orders.txt");
        rename("temp.txt", "orders.txt");
    }

    /** 
     * 从文件读取并显示所有订单
     * @description 从orders.txt文件中读取所有订单信息，并逐条打印。
     * @complexity 时间复杂度：O(n)，n为文件中的订单数量。
    */
    void read_order() {
        ifstream fin("orders.txt");
        while (fin >> order_id >> company_name >> product_name >> product_price >> order_quantity >> order_amount) {
            display_order();
            cout << endl;
        }
        fin.close();
    }

    /** 
     * 根据订单编号搜索订单
     * @param id 要搜索的订单编号。
     * @description 在orders.txt文件中搜索订单编号，并显示匹配的订单信息。
     * @complexity 时间复杂度：O(n)，n为文件中的订单数量。
     */
    void search_order(char* id) {
        ifstream fin("orders.txt");
        bool found = false;
        while (fin >> order_id >> company_name >> product_name >> product_price >> order_quantity >> order_amount) {
            if (strcmp(order_id, id) == 0) {
                display_order();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "未找到该订单！" << endl;
        }
        fin.close();
    }

    /** 
     * 根据订单编号删除订单
     * @param id 要删除的订单编号。
     * @description 从orders.txt文件中删除指定的订单编号。
     * @complexity 时间复杂度：O(n)，n为文件中的订单数量。
    */
    void delete_order(char* id) {
        ifstream fin("orders.txt");
        ofstream fout("temp.txt");
        bool found = false;
        while (fin >> order_id >> company_name >> product_name >> product_price >> order_quantity >> order_amount) {
            if (strcmp(order_id, id) != 0) {
                fout << order_id << " " << company_name << " " << product_name << " " << product_price << " " << order_quantity << " " << order_amount << endl;
            } else {
                found = true;
            }
        }
        fin.close();
        fout.close();
        remove("orders.txt");
        rename("temp.txt", "orders.txt");
        if (found) {
            cout << "订单已删除！" << endl;
        } else {
            cout << "未找到该订单！" << endl;
        }
    }

    /** 
     * 统计指定公司的订单总额
     * @param company 要统计的公司名称。
     * @description 统计并打印指定公司所有订单的总额。
     * @complexity 时间复杂度：O(n)，n为文件中的订单数量。
     */
    void total_order_amount(char* company) {
        ifstream fin("orders.txt");
        double total = 0;
        while (fin >> order_id >> company_name >> product_name >> product_price >> order_quantity >> order_amount) {
            if (strcmp(company_name, company) == 0) {
                total += order_amount;
            }
        }
        fin.close();
        cout << "公司 " << company << " 的所有订单总额为：" << total << endl;
    }
};


/** 
 * 主函数
 * @description 提供用户界面，允许用户选择不同的订单管理操作。
 * @complexity 时间复杂度：O(1)，主循环中的操作依赖于用户输入。
 */
int main() {
    Order order;
    int choice;
    char id[20], company[50];
    while (true) {
        cout << "请选择操作：" << endl;
        cout << "1. 添加订单" << endl;
        cout << "2. 浏览订单" << endl;
        cout << "3. 查询订单" << endl;
        cout << "4. 删除订单" << endl;
        cout << "5. 统计订单总额" << endl;
        cout << "6. 退出" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                order.add_order();
                order.write_order();
                break;
            case 2:
                order.read_order();
                break;
            case 3:
                cout << "请输入要查询的订单编号：";
                cin >> id;
                order.search_order(id);
                break;
            case 4:
                cout << "请输入要删除的订单编号：";
                cin >> id;
                order.delete_order(id);
                break;
            case 5:
                cout << "请输入要统计的公司名称：";
                cin >> company;
                order.total_order_amount(company);
                break;
            case 6:
                return 0;
            default:
                cout << "输入错误，请重新输入！" << endl;
                break;
        }
    }
    return 0;
}
