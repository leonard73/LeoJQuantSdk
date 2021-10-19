#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include  <iostream>
#include  <string>
#include  <sstream>
#include  <curl/curl.h>
#include  <vector>
#include  <strDecode.h>
#include  <iomanip>
namespace stock_sdk_space{
typedef struct GLOBAL_REQUEST_t
{
    std::string token;
    std::string phone_num;
    std::string pwd;
    CURL *pCurl;
    CURLcode res;
}GLOBAL_REQUEST;
#define STOCK_LABEL_SH_A 0
#define STOCK_LABEL_SZ_A 1
#define STOCK_LABEL_SH_K 2
#define STOCK_LABEL_SZ_Z 3
#define STOCK_LABEL_SZ_C 4
typedef struct STOCK_DATA_DATE_t
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
}STOCK_DATA_DATE; // 4bytes
typedef struct STOCK_PRICE_t
{
    STOCK_DATA_DATE date;
    float open;
    float close;
    float high;
    float low;
    uint32_t volume;
    float money;
    uint32_t paused;
    float high_limit;
    float low_limit;
    float avg;
    float pre_close;
}STOCK_PRICE;
typedef struct STOCK_DATA_t
{
    uint32_t stock_code;
    std::string stock_label;
    std::string stock_label_all;
    std::string stock_nameCH;
    std::string stock_nameAB;
    STOCK_DATA_DATE stock_start_date;
    STOCK_DATA_DATE stock_end_date;
    std::vector<STOCK_PRICE> price_info_10days;
}STOCK_DATA;
size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream);
class stock_sdk
{
    private: GLOBAL_REQUEST request;
    private: std::vector<STOCK_DATA> stock_array;
    private: void sdk_init();
    private: void save_str_into_stock_array(std::vector <std::string> onelineVector);
    private: void save_priceInfo_targetStock(std::vector <std::string> onelineVector,STOCK_DATA &target_stock);
    private: void set_stock_date_from_date_str(const char* date,STOCK_DATA_DATE & stock_date);
    private: void convert_stream_to_stock_data(std::string stream_raw);
    private: void convert_stream_to_price_data(std::string stream_raw,STOCK_DATA &target_stock);
    public: stock_sdk();
    public: stock_sdk(const char * phone_num, const char * pwd);
    public: void set_jq_account(char * phone_num, char * pwd);
    public: void get_stock_data();
    public: void get_price_data();
    public: void log_stock_info_all();
    public: void log_stock_info_by_codeNB(uint32_t codeNB);
    public: void get_priceInfo_10Days(uint32_t stock_id);
    public: void find_strong10days_week3days(float rate10,float rate3);
    public: ~stock_sdk();
};

};
#endif //__CONTROLLER_H__