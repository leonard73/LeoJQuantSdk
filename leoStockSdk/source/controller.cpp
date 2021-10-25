#include <controller.h>
using namespace stock_sdk_space;
#define LOGLINE_STR(X) (std::cout<<X<<std::endl)
#define LOGLINE_STR_INT(S,I) (std::cout<<S<<std::setw(6)<<std::setfill('0')<<I<<std::endl)
size_t stock_sdk_space::receive_data(void *ptr,size_t size,size_t nmemb,void *stream){
    std::string data((const  char*) ptr,  (size_t) size * nmemb);
    *((std::stringstream*) stream)  << data;
    return size * nmemb;
}
void stock_sdk::set_jq_account(char * phone_num, char * pwd)
{
    this->request.phone_num = phone_num;
    this->request.pwd=pwd;
}
stock_sdk::stock_sdk()
{
    this->request.phone_num = "13918934560";
    this->request.pwd="Panjiaqi7395";
    this->sdk_init();
}
stock_sdk::stock_sdk(const char * phone_num, const char * pwd)
{
    this->request.phone_num = phone_num;
    this->request.pwd=pwd;
    this->sdk_init();
}
stock_sdk::~stock_sdk()
{
    curl_easy_cleanup(this->request.pCurl);
    curl_global_cleanup();  
}
void stock_sdk::sdk_init()
{
    curl_global_init(CURL_GLOBAL_ALL);
    this->request.pCurl =  curl_easy_init();
    if  (NULL  != this->request.pCurl)  {
        std::stringstream out;
        curl_easy_setopt(this->request.pCurl, CURLOPT_TIMEOUT,  3);
        curl_easy_setopt(this->request.pCurl, CURLOPT_URL,  "https://dataapi.joinquant.com/apis");
        curl_slist *plist =  curl_slist_append(NULL,  "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(this->request.pCurl, CURLOPT_HTTPHEADER, plist);
        char szJsonData[300];
        sprintf(szJsonData,"{\"method\": \"get_token\",\"mob\": \"%s\",\"pwd\": \"%s\"}",this->request.phone_num.c_str(),this->request.pwd.c_str());
        curl_easy_setopt(this->request.pCurl, CURLOPT_POSTFIELDS, szJsonData);
        curl_easy_setopt(this->request.pCurl, CURLOPT_WRITEFUNCTION, receive_data);
        curl_easy_setopt(this->request.pCurl, CURLOPT_WRITEDATA,  &out);
        this->request.res =  curl_easy_perform(this->request.pCurl);
        this->request.token=  out.str();
        LOGLINE_STR(this->request.token);
    }
}
// std::vector<std::string> sub_string_array;
// void statistic_comma_nb(std::string str)
// {
//     std::cout<<"stocks' size is : "<<str.size()/5<<std::endl;
//     std::cout<<"stocks' size is : "<<str.at(str.size()-6)<<std::endl;
//     static int line_nb=0;
//     int comma_acumulator=0;
//     char array_tmp[100];
//     int array_tmp_count=0;
//     for(auto i=str.begin();i<=str.end();i++)
//     {
//         array_tmp[array_tmp_count++]=*i;
//         if((*i)=='\n')
//         {
            
//             array_tmp[array_tmp_count-1]='\0';
//             // stock_name_array.copy(array_tmp,array_tmp_count,0);
//             std::string stock_name_array=array_tmp;
//             sub_string_array.push_back(stock_name_array);
//             std::cout<<array_tmp<<std::endl;
//             comma_acumulator++;
//             line_nb++;
//             array_tmp_count=0;
//             // std::cout<<i[0]<<comma_nb<<std::endl;
//             // if(comma_acumulator==)
//         }
//     }
//     std::cout<<"line_nb is : "<<line_nb<<std::endl;
//     std::cout<<"line_nb is : "<<sub_string_array.size()<<std::endl;
//     //decode the first line
//     auto first_line_string = sub_string_array.at(0);
//     int id=0;
//     std::vector<std::string> item_name;
//     char array_t[100];
//     int array_t_count=0;
//     for(int i=0;i<first_line_string.size()+1;i++)
//     {
//         array_t[array_t_count++] = (first_line_string.c_str()[i]);
//         if(first_line_string.c_str()[i]==',' || first_line_string.c_str()[i]=='\0')
//         {
//             array_t[array_t_count-1] = '\0';
//             std::string item = array_t;
//             item_name.push_back(item);
//             array_t_count=0;
//         }
//     }
//     std::cout<<"item nb is "<<item_name.size()<<std::endl;
//     for(int i=0;i<item_name.size();i++)
//     {
//         std::cout<<"item["<<i<<"]: "<<item_name.at(i).c_str()<<std::endl;
//     }
// }
void stock_sdk::set_stock_date_from_date_str(const char* date,STOCK_DATA_DATE & stock_date)
{
        {
            char year[5] = {date[0],date[1],date[2],date[3],'\0'};
            std::string string_start_y = year;
            std::stringstream ss;
            ss<<string_start_y;
            ss>>stock_date.year;   
        }  
        {
            char month[3] = {date[5],date[6],'\0'};
            std::string string_start_m = month;
            std::stringstream ss;
            ss<<string_start_m;
            ss>>stock_date.month;   
        }  
        {
            char day[3] = {date[8],date[9],'\0'};
            std::string string_start_d = day;
            std::stringstream ss;
            ss<<string_start_d;
            ss>>stock_date.day;   
        }   
}
void stock_sdk::save_str_into_stock_array(std::vector <std::string> onelineVector)
{
    STOCK_DATA save_stock_data;
    {
        auto str_code_label = onelineVector.at(0).c_str();
        save_stock_data.stock_label_all = str_code_label;
        char code_nb_str[7] = {str_code_label[0],str_code_label[1],str_code_label[2],str_code_label[3],str_code_label[4],str_code_label[5],'\0'};
        std::string string_code_nb = code_nb_str;
        std::stringstream ss1;
        ss1<< string_code_nb;
        uint32_t int_code_nb;
        ss1>>int_code_nb;
        save_stock_data.stock_code=int_code_nb;
        // LOGLINE_STR_INT("code_nb: ",int_code_nb);
        #define LABEL_SIZE_DEFAULT (50)
        char load_label_raw[LABEL_SIZE_DEFAULT];
        for(int i=0;i<LABEL_SIZE_DEFAULT;i++)
        {
            load_label_raw[i] = code_nb_str[7+i];
            if(load_label_raw[i]=='\0')
            {
                break;
            }
        }
        save_stock_data.stock_label = load_label_raw;
        #undef LABEL_SIZE_DEFAULT
    }
    {
        auto str_nameCH= onelineVector.at(1).c_str();
        save_stock_data.stock_nameCH=str_nameCH;
    }
    {
        auto str_nameAB= onelineVector.at(2).c_str();
        save_stock_data.stock_nameAB=str_nameAB;      
    }
    {
        auto str_start_date= onelineVector.at(3).c_str();
        set_stock_date_from_date_str(str_start_date,save_stock_data.stock_start_date);
    }
    {
        auto str_end_date= onelineVector.at(4).c_str();
        set_stock_date_from_date_str(str_end_date,save_stock_data.stock_end_date);
    }
    this->stock_array.push_back(save_stock_data);
}
void stock_sdk::convert_stream_to_stock_data(std::string stream_raw)
{
    std::vector <std::string> lines_str;
    decode_str_by_lines(lines_str,stream_raw);
    for(int lineID=1;lineID<lines_str.size();lineID++)
    {
        auto string_line = lines_str.at(lineID);
        std::vector <std::string> str_elem;
        decode_str_by_comma_perline(str_elem,string_line);
        save_str_into_stock_array(str_elem);
    }
}
void stock_sdk::get_stock_data()
{
    std::stringstream data;
    std::string params =  "{\"method\": \"get_all_securities\",\"token\": \""+this->request.token+"\",\"code\": \"stock\"}";
    const  char* jsonData =  (char*)params.c_str();
    curl_easy_setopt(this->request.pCurl, CURLOPT_POSTFIELDS, jsonData);
    curl_easy_setopt(this->request.pCurl, CURLOPT_WRITEDATA,  &data);
    this->request.res =  curl_easy_perform(this->request.pCurl);
    LOGLINE_STR("GET STOCK DATA FROM HTTP SUCCESSFULLY");
    this->convert_stream_to_stock_data(data.str());
    // std::cout <<  data.str()  << std::endl;
}
void stock_sdk::get_price_data()
{
    std::stringstream data;
    char params_ch[500];
    sprintf(params_ch,"{\"method\": \"%s\",\"token\": \"%s\",\"code\": \"%s\",\"count\": \"%s\",\"unit\": \"%s\"}","get_price",this->request.token.c_str(),"600000.XSHG","10","1d");
    const  char* jsonData =  params_ch;
    curl_easy_setopt(this->request.pCurl, CURLOPT_POSTFIELDS, jsonData);
    curl_easy_setopt(this->request.pCurl, CURLOPT_WRITEDATA,  &data);
    this->request.res =  curl_easy_perform(this->request.pCurl);
    std::cout <<  data.str()  << std::endl;
}
void stock_sdk::log_stock_info_all()
{
    for(int i=0;i<this->stock_array.size();i++)
    {
        auto stock = this->stock_array.at(i);
        LOGLINE_STR("STOCK_NAME: "+stock.stock_nameCH);
        LOGLINE_STR_INT("STOCK_CODE: ",stock.stock_code);
    }
}
void stock_sdk::log_stock_info_by_codeNB(uint32_t codeNB)
{
    for(int i=0;i<this->stock_array.size();i++)
    {
        auto stock = this->stock_array.at(i);
        if(stock.stock_code==codeNB)
        {
            LOGLINE_STR("STOCK_NAME: "+stock.stock_nameCH);
            LOGLINE_STR_INT("STOCK_CODE: ",stock.stock_code);
            get_priceInfo_10Days(codeNB);
            LOGLINE_STR_INT("close price: ",this->stock_array.at(i).price_info_10days.at(this->stock_array.at(i).price_info_10days.size()-1).close);
        }
    }
}
void stock_sdk::save_priceInfo_targetStock(std::vector <std::string> onelineVector,STOCK_DATA &target_stock)
{
    STOCK_PRICE stock_price;
    auto date_str=onelineVector.at(0).c_str();
    set_stock_date_from_date_str(date_str,stock_price.date);
    {
        std::stringstream ss;
        ss << onelineVector.at(1);
        ss>>stock_price.open;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(2);
        ss>>stock_price.close;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(3);
        ss>>stock_price.high;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(4);
        ss>>stock_price.low;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(5);
        ss>>stock_price.volume;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(6);
        ss>>stock_price.money;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(7);
        ss>>stock_price.paused;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(8);
        ss>>stock_price.high_limit;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(9);
        ss>>stock_price.low_limit;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(10);
        ss>>stock_price.avg;
    }
    {
        std::stringstream ss;
        ss << onelineVector.at(11);
        ss>>stock_price.pre_close;
    }

    target_stock.price_info_10days.push_back(stock_price);
}
void stock_sdk::convert_stream_to_price_data(std::string stream_raw,STOCK_DATA &target_stock) 
{
    std::vector <std::string> lines_str;
    decode_str_by_lines(lines_str,stream_raw);
    // LOGLINE_STR_INT("decode_str_by_lines ",9);
    for(int lineID=1;lineID<lines_str.size();lineID++)
    {
        auto string_line = lines_str.at(lineID);
        std::vector <std::string> str_elem;
        decode_str_by_comma_perline(str_elem,string_line);
        save_priceInfo_targetStock(str_elem,target_stock);
    }
}
void stock_sdk::get_priceInfo_10Days(uint32_t stock_id)
{

        auto stock = this->stock_array.at(stock_id);
        std::stringstream data;
        char params_ch[500];
        sprintf(params_ch,"{\"method\": \"%s\",\"token\": \"%s\",\"code\": \"%s\",\"count\": \"%s\",\"unit\": \"%s\"}","get_price",this->request.token.c_str(),stock.stock_label_all.c_str(),"10","1d");
        const  char* jsonData =  params_ch;
        curl_easy_setopt(this->request.pCurl, CURLOPT_POSTFIELDS, jsonData);
        curl_easy_setopt(this->request.pCurl, CURLOPT_WRITEDATA,  &data);
        this->request.res =  curl_easy_perform(this->request.pCurl);
            // std::cout <<  data.str()  << std::endl;
            // LOGLINE_STR_INT("loadprice ok :",i);
        convert_stream_to_price_data(data.str(),this->stock_array.at(stock_id));
}
void stock_sdk::find_strong10days_week3days(float rate10,float rate3)
{
    for(int i=0;i<this->stock_array.size();i++)
    {
        // LOGLINE_STR_INT("finding : ",this->stock_array.at(i).stock_code);
        get_priceInfo_10Days(i);
        uint32_t today_id = this->stock_array.at(i).price_info_10days.size()-1;
        uint32_t last10day_id = this->stock_array.at(i).price_info_10days.size()>=10?(this->stock_array.at(i).price_info_10days.size()-10):0;
        uint32_t last3day_id = this->stock_array.at(i).price_info_10days.size()>=3?(this->stock_array.at(i).price_info_10days.size()-3):0;
        float today_close =  this->stock_array.at(i).price_info_10days.at(today_id).close;
        float last10day_close = this->stock_array.at(i).price_info_10days.at(last10day_id).close;
        float last3day_close = this->stock_array.at(i).price_info_10days.at(last3day_id).close;
        float rate10_cpt =  (today_close-last10day_close)/last10day_close;
        float rate3_cpt =  (today_close-last3day_close)/last3day_close;
        if(rate10_cpt>=rate10 && rate3_cpt<=rate3)
        {
            LOGLINE_STR_INT("FIND! : ",this->stock_array.at(i).stock_code);
        }
        else
        {
            // LOGLINE_STR_INT("NOT FIND! : ",this->stock_array.at(i).stock_code);
        }
    }
    LOGLINE_STR_INT("find stock finished ",0);
}