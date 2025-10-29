#include "Headers/operations.h"

/*
* Function: void parseFile(hashTable<string, entry*>& h, avl_map<string, vector<entry*>>& map)
* Description: Parses files and places data into hash and avl maps
* Input parameters: hashTable<string, entry*>& h, avl_map<string, vector<entry*>>& map
* Returns: void
* Preconditions: h and map must be empty.
* Postconditions: Places data into hash and avl maps.
*/
void parseFile(hashTable<string, entry*>& h, avl_map<string, vector<entry*>>& map)
{
    ifstream inputStream("Resources/marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    string line, templine, stringStream;
    stringstream streamS, tempStream;
    entry* data;
    avl_map<string, vector<entry*>>::Iterator tempIterator;

    getline(inputStream, stringStream, '\n');

    if(inputStream.is_open())
    {
        while(getline(inputStream, stringStream, '\n'))//get full line
        {
            data = new entry(); //reset data
            if(data != nullptr)
            {
                while(stringStream.find("\"\"") != string::npos)//do some clean up
                {
                    stringStream.erase(stringStream.find("\"\""), 2);
                }
                streamS.clear();
                streamS.str(stringStream);//set cleaned up line as stream to parse through

                getline(streamS, line, ',');//now parse through line
                data->id = line;
                getline(streamS, line, ',');
                if(line[0] == '\"' && line[line.size() - 1] != '\"')
                {
                    getline(streamS, templine, '\"');
                    line += templine;
                    getline(streamS, templine, ',');
                    line.erase(0,1);
                }
                data->productName = line;
                getline(streamS, line, ',');
                data->brandName = line;
                getline(streamS, line, ',');
                data->asin = line;
                getline(streamS, line, ',');
                if(line[0] == '\"' && line[line.size() - 1] != '\"')
                {
                    getline(streamS, templine, '\"');
                    line += templine;
                    getline(streamS, templine, ',');
                    line.erase(0,1);
                }
                else if(line[0] == '\0')
                {
                    line = "NA";
                }
                tempStream.clear();
                tempStream.str(line);
                for(int i = count(line.begin(), line.end(), '|'); i > 0; i--)//seperate categories, treating NA as its own category
                {
                    getline(tempStream, templine, '|');
                    while(templine.find(" ") != string::npos)
                    {
                        templine.erase(templine.find(" "),1);
                    }
                    data->categories.push_back(templine);
                }
                getline(tempStream, templine, ',');
                while(templine.find(" ") != string::npos)
                {
                    templine.erase(templine.find(" "),1);
                }
                data->categories.push_back(templine);
                getline(streamS, line, ',');
                data->eanCode = line;
                getline(streamS, line, ',');
                data->listPrice = line;
                getline(streamS, line, ',');
                data->sellingPrice = line;
                getline(streamS, line, ',');
                data->quanity = line;
                getline(streamS, line, ',');
                data->modelNumber = line;
                getline(streamS, line, ',');
                if(line[0] == '\"' && line[line.size() - 1] != '\"')
                {
                    getline(streamS, templine, '\"');
                    line += templine;
                    getline(streamS, templine, ',');
                    line.erase(0,1);
                }
                data->aboutProduct = line;
                getline(streamS, line, ',');
                data->productSpecification = line;
                getline(streamS, line, ',');
                if(line[0] == '\"' && line[line.size() - 1] != '\"')
                {
                    getline(streamS, templine, '\"');
                    line += templine;
                    getline(streamS, templine, ',');
                    line.erase(0,1);
                }
                data->techDetails = line;
                getline(streamS, line, ',');
                data->shippingWeight = line;
                getline(streamS, line, ',');
                data->productDimensions = line;
                getline(streamS, line, ',');
                data->image = line;
                getline(streamS, line, ',');
                data->variants = line;
                getline(streamS, line, ',');
                data->sku = line;
                getline(streamS, line, ',');
                data->productUrl = line;
                getline(streamS, line, ',');
                data->stock = line;
                getline(streamS, line, ',');
                data->productDetails = line;
                getline(streamS, line, ',');
                data->dimensions = line;
                getline(streamS, line, ',');
                data->color = line;
                getline(streamS, line, ',');
                data->ingredients = line;
                getline(streamS, line, ',');
                data->directionToUse = line;
                getline(streamS, line, ',');
                data->isAmazonSeller = line;
                getline(streamS, line, ',');
                data->sizeQuantityVariant = line;
                getline(streamS, line, '\n');
                data->productDescription = line;

                h.insert(data->id, data);
                for(int i = data->categories.size() - 1; i >= 0; i--)
                {
                    templine = data->categories[i];
                    tempIterator = map.find(templine);
                    if(tempIterator.current != nullptr)
                    {
                        tempIterator.current->value.push_back(data);
                    }
                    else
                    {
                        map.insert(templine, vector<entry*>());
                        tempIterator = map.find(templine);
                        tempIterator.current->value.push_back(data);
                    }
                }
                //cout << *data << endl;
            }
        }
    }

}

/*
* Function: void Pause()
* Description: Pauses screen and continues when user presses enter.
* Input parameters: void
* Returns: void
* Preconditions: N/A.
* Postconditions: Prints to screen.
*/
void Pause()
{
    cout << "\nPress Enter to continue\n";
    cin.get();
    //cin.get(); //maybe put back?
}

/*
* Function: void relieveHeap(hashTable<string, entry*>& h)
* Description: Relieves data allocated from ParseFile function.
* Input parameters: hashTable<string, entry*>& h
* Returns: void
* Preconditions: Data must be allocated in data field all data fields of hash
* Postconditions: Removes allocated data from value data field in all values of hash.
*/
void relieveHeap(hashTable<string, entry*>& h)
{
    for(int i = 0; i < 30000; i++)
    {
        if(h.arr[i].data != nullptr)
        {
            delete h.arr[i].data;
        }
    }

}
