#include <curl/curl.h>
#include <stdio.h>
#include <inttypes.h>

CURLcode curl_easy_setopt_int(CURL *handle, CURLoption option, ssize_t value)
{
    return curl_easy_setopt(handle, option, value);
}

CURLcode curl_easy_setopt_word(CURL *handle, CURLoption option, size_t value)
{
    return curl_easy_setopt(handle, option, value);
}

ssize_t __curlopt_upload()
{
    return CURLOPT_UPLOAD;
}

ssize_t __curlopt_url()
{
    return CURLOPT_URL;
}

ssize_t __curlopt_postfield()
{
    return CURLOPT_POSTFIELDS;
}

ssize_t __curlopt_postfieldsize()
{
    return CURLOPT_POSTFIELDSIZE;
}

ssize_t __curlopt_verbose()
{
    return CURLOPT_VERBOSE;
}

void __curl_setjson(CURL* curl)
{
    struct curl_slist *hs=NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
}
