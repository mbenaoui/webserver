#include "include/Prasing_Request.hpp"
#include <bits/stdc++.h>

int Prasing_Request::check_first_line(std::string first_line)
{
    methode = strtok((char *)first_line.c_str(), " ");
    if (methode != "GET" && methode != "POST" && methode != "DELETE")
    {
        std ::cout << "405 Method Not Allowed" << std::endl;
        status = 405;
        return (0);
    }
    char *urlll = strtok(NULL, " ");
    url = urlll;
    if (urlll[0] != '/')
    {
        std ::cout << "400 Bad Request" << std::endl;
        status = 400;
        return (0);
    }
    std ::string htb = strtok(NULL, " ");
    if (htb != "HTTP/1.1")
    {
        std::cout << "505 HTTP Version Not Supported" << std::endl;
        status = 505;
        return (0);
    }
    if (strchr(url.c_str(), '?'))
    {
        strtok((char *)url.c_str(), "?");
        char *str = strtok(NULL, "?");
        budy_url = str;
        std ::cout << budy_url << std::endl;
    }
    return (1);
}

std ::vector<std ::string> split(std::string str, std::string delimiter)
{
    std ::vector<std ::string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            int idx = str.find(delimiter, start);
            if (idx == std ::string::npos)
            {
                break;
            }

            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}
void Prasing_Request::prasing_headr(std ::string headrs)
{

    std ::vector<std ::string> res = split(headrs, "\r\n");
    for (int i = 0; i < res.size(); i++)
    {
        std ::string key = res[i].substr(0, res[i].find(":"));
        std ::string value = res[i].substr(res[i].find(" "));
        mymap.insert(std ::pair<std ::string, std::string>(key, value));
    }
    if (status == 200)
    {
        if (methode == "POST" && mymap["Content-Type"].empty())
        {
            std ::cout << "error on Content-Type !!!" << std::endl;
            status = 400;
            return;
        }
        if (methode == "POST" && (mymap["Content-Length"].empty() || atoi(mymap["Content-Length"].c_str()) < 0))
        {
            std ::cout << "411 Length Required" << std::endl;
            status = 411;
            return;
        }
        if (mymap["HOST"].empty())
        {
            std ::cout << "error om HOST !!" << std ::endl;
            status = 400;
            return;
        }
        if (atoi(mymap["Content-Length"].c_str()) > 2000)
        {
            std ::cout << "eroore on size Content-Length " << std::endl;
            status = 400;
            return;
        }
        if (mymap["Transfer-Encoding"] != "chunked")
        {
            std ::cout << "error on Transfer-Encoding !!!" << std::endl;
            this->status = 400;
        }
        if (mymap["Transfer-Encoding"] == "chunked")
        {
            this->status = 200;
        }
    }
}
Prasing_Request::Prasing_Request(std::string hedr)
{
    if (!hedr[0])
        return;
    this->status = 200;
    std ::string first;
    std ::string hdr;
    int i = 0;
    while (i < hedr.length())
    {
        if (hedr.at(i) == '\r' || hedr.at(i) == '\n')
            break;
        i++;
    }
    first = hedr.substr(0, i);
    hdr = hedr.substr(i, hedr.find("\r\n\r\n"));
    if(!check_first_line(first))
        return ;
    prasing_headr(hdr);
    if(this->status != 200)
        return ;
}

std ::string Prasing_Request ::get_methode()
{
    return this->methode;
}
std ::string Prasing_Request ::get_url()
{
    return this->url;
}
std ::string Prasing_Request ::get_budy_url()
{
    return this->budy_url;
}
int Prasing_Request ::get_status()
{
    return this->status;
}
int main()
{
    Prasing_Request rp("dfhd: cvf\r\njvhd: fhvgh\r\nvfhshj: dcfdv\r\nhkvfdhk: vhkghfhh\r\n\r\n");
    // int status = rp.check_first_line(cheker);
    //    std ::cout << "abc\r 45" << std::endl;
}