#ifndef ENTRY
#define ENTRY

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class entry
{
public:
entry()
{
    id = "";
    productName = "";
    brandName = "";
    asin = "";
    categories = vector<string>();
    eanCode = "";
    listPrice = "";
    sellingPrice = "";
    quanity = "";
    modelNumber = "";
    aboutProduct = "";
    productSpecification = "";
    techDetails = "";
    shippingWeight = "";
    productDimensions = "";
    image = "";
    variants = "";
    sku = "";
    productUrl = "";
    stock = "";
    productDetails = "";
    dimensions = "";
    color = "";
    ingredients = "";
    directionToUse = "";
    isAmazonSeller = "";
    sizeQuantityVariant = "";
    productDescription = "";
};

string id;
string productName;
string brandName;
string asin;
vector<string> categories;
string eanCode;
string listPrice;
string sellingPrice;
string quanity;
string modelNumber;
string aboutProduct;
string productSpecification;
string techDetails;
string shippingWeight;
string productDimensions;
string image;
string variants;
string sku;
string productUrl;
string stock;
string productDetails;
string dimensions;
string color;
string ingredients;
string directionToUse;
string isAmazonSeller;
string sizeQuantityVariant;
string productDescription;

//overloaded < operator 
bool operator<(const entry& other) const {
    return this->id < other.id;
}

private:

};

//overloaded << operator for output stream
inline ostream& operator<<(ostream& stream, const entry& data)
{
    stream << "ID: " << data.id << ", Product Name: " << data.productName;
    return stream;
}

#endif