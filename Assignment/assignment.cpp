#include <bits/stdc++.h>

using namespace std;

class Product
{
private:
    int _pid;
    string _pname;
    double _price;

public:
    Product(int id, string name, double price) : _pid(id), _pname(name), _price(price) {}

    string getProductName() {
        return _pname;
    }

    double getProductPrice() {
        return _price;
    }

    void displayProductInfo() {
        cout<<"Product ID: "<<_pid<<"\nProduct Name: "<<_pname<<"\nProduct Price: "<<_price<<endl;
    }
};

class Sales
{
private:
    int _pid;
    int _invoice; 

public:
    Sales(int id, int invoice) : _pid(id), _invoice(invoice) {}

    int getId() {
        return _pid;
    }

    void displayProductInfo() {
        cout<<"Product ID: "<<_pid<<"\nInvoice Number: "<<_invoice<<endl;
    }
};

void displaySalesOfEachProduct(vector<Product> &product_list, const vector<Sales> &sales_list) {
    map<int, int> salesPerProduct;

    for(auto sale : sales_list) {
        salesPerProduct[sale.getId()]++;
    }

    for(auto itr : salesPerProduct) {
        int proId = itr.first - 1;
        cout<<"Total sales of "<<product_list[proId].getProductName()<<"(ID: "<<itr.first<<"): "<<itr.second<<" unit = Rs. "<<product_list[proId].getProductPrice() * itr.second <<endl;
    }
    
}

int main() {
    // For Products
    vector<Product> product_list;
    string str;
    ifstream productFile("Products.csv");
    getline(productFile, str);

    while (getline(productFile, str))
    {
        int id;
        string name;
        double price;

        stringstream tempStream(str);
        vector<string> tempStr;

        while (tempStream.good()) {
            string substr;
            getline(tempStream, substr, ';');
            tempStr.push_back(substr);
        }

        id = stoi(tempStr[0]);
        name = tempStr[1];
        price = stod(tempStr[2]);

        product_list.push_back({id, name, price});
    }
    productFile.close();

    for(int i = 0; i < product_list.size(); i++) {
        product_list[i].displayProductInfo();
    }


    cout<<"\n--------------------"<<endl;
    // For Sales
    vector<Sales> sales_list;
    str = "";
    ifstream salesFile("Sales.csv");
    getline(salesFile, str);

    while (getline(salesFile, str))
    {
        int id;
        int invoice;

        stringstream tempStream(str);
        vector<string> tempStr;

        while (tempStream.good()) {
            string substr;
            getline(tempStream, substr, ';');
            tempStr.push_back(substr);
        }

        id = stoi(tempStr[0]);
        invoice = stoi(tempStr[1]);

        sales_list.push_back({id, invoice});
    }

    salesFile.close();

    for(int i = 0; i < sales_list.size(); i++) {
        sales_list[i].displayProductInfo();
    }

    cout<<"\n\nTotal sales of each product:"<<endl;
    displaySalesOfEachProduct(product_list, sales_list);

    return 0;
}