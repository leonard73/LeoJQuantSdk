#include <strDecode.h>
#define LOG_TAG " [STR_DECODE] "
#define LOGLINE_STR_INT(s,i) std::cout<<LOG_TAG<<s<<" "<<i<<std::endl
#define LOGLINE_STR_INT_STR_STR(s1,i1,s2,s3) std::cout<<LOG_TAG<<s1<<" "<<i1<<s2<<" "<<s3<<std::endl
void decode_str_by_lines(std::vector <std::string> & lines_str,std::string string_raw)
{
    // LOGLINE_STR_INT("total char num:",string_raw.size());
    static int line_nb=0;
    int comma_acumulator=0;
    char array_tmp[100];
    int array_tmp_count=0;
    for(auto i=string_raw.begin();i<=string_raw.end();i++)
    {
        array_tmp[array_tmp_count++]=*i;
        if((*i)=='\n' ||  (*i)=='\0' )
        {
            
            array_tmp[array_tmp_count-1]='\0';
            // stock_name_array.copy(array_tmp,array_tmp_count,0);
            std::string stock_name_array=array_tmp;
            lines_str.push_back(stock_name_array);
            // std::cout<<array_tmp<<std::endl;
            comma_acumulator++;
            line_nb++;
            array_tmp_count=0;
        }
    }
    // for(int i=0;i<5;i++)
    // {
    //     LOGLINE_STR_INT_STR_STR("lines_str[",i,"]data:",lines_str.at(i).c_str());
    // }
}
void decode_str_by_comma_perline(std::vector <std::string> & str_elem,std::string string_oneLine)
{
        //decode the first line
    char array_t[400];
    int array_t_count=0;
    for(int i=0;i<string_oneLine.size()+1;i++)
    {
        array_t[array_t_count++] = (string_oneLine.c_str()[i]);
        if(string_oneLine.c_str()[i]==',' || string_oneLine.c_str()[i]=='\0')
        {
            array_t[array_t_count-1] = '\0';
            std::string item = array_t;
            str_elem.push_back(item);
            array_t_count=0;
        }
    }
    // std::cout<<"item nb is "<<str_elem.size()<<std::endl;
    // for(int i=0;i<str_elem.size();i++)
    // {
    //     std::cout<<"item["<<i<<"]: "<<str_elem.at(i).c_str()<<std::endl;
    // }
}
