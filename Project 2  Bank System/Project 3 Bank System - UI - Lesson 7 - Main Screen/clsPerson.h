#pragma once // íÖãä ÚÏã ÊÖãíä åĞÇ Çáãáİ ÃßËÑ ãä ãÑÉ İí ÇáÊÑÌãÉ

#include <iostream> // ÊÖãíä ãßÊÈÉ ÇáÅÏÎÇá æÇáÅÎÑÇÌ ÇáŞíÇÓíÉ
#include <string> // ÊÖãíä ãßÊÈÉ ÇáÓáÇÓá ÇáŞíÇÓíÉ
using namespace std; // ÇÓÊÎÏÇã İÖÇÁ ÇáÃÓãÇÁ std

class clsPerson // ÊÚÑíİ ÇáİÕíáÉ clsPerson
{

private: // ŞÓã ÎÇÕ ááÈíÇäÇÊ ÇáÎÇÕÉ

    string _FirstName; // ÓáÓáÉ ÎÇÕÉ ÊÍãá ÇáÇÓã ÇáÃæá
    string _LastName; // ÓáÓáÉ ÎÇÕÉ ÊÍãá ÇáÇÓã ÇáÃÎíÑ
    string _Email; // ÓáÓáÉ ÎÇÕÉ ÊÍãá ÇáÈÑíÏ ÇáÅáßÊÑæäí
    string _Phone; // ÓáÓáÉ ÎÇÕÉ ÊÍãá ÑŞã ÇáåÇÊİ

public: // ŞÓã ÚÇã ááæÙÇÆİ ÇáÚÇãÉ

    // ãßæä ááİÆÉ íÃÎĞ Şíã ÇáÃÓãÇÁ ÇáÃæá æÇáÃÎíÑ æÇáÈÑíÏ ÇáÅáßÊÑæäí æÑŞã ÇáåÇÊİ
    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {

        _FirstName = FirstName; // ÊÚííä ÇáÇÓã ÇáÃæá
        _LastName = LastName; // ÊÚííä ÇáÇÓã ÇáÃÎíÑ
        _Email = Email; // ÊÚííä ÇáÈÑíÏ ÇáÅáßÊÑæäí
        _Phone = Phone; // ÊÚííä ÑŞã ÇáåÇÊİ
    }

    //Property Set
    void SetFirstName(string FirstName) // æÙíİÉ áÊÚííä ÇáÇÓã ÇáÃæá
    {
        _FirstName = FirstName; // ÊÚííä ÇáÇÓã ÇáÃæá
    }

    //Property Get
    string GetFirstName() // æÙíİÉ ááÍÕæá Úáì ÇáÇÓã ÇáÃæá
    {
        return _FirstName; // ÅÑÌÇÚ ÇáÇÓã ÇáÃæá
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName; // ÎÇÕíÉ ááÍÕæá æÊÚííä ÇáÇÓã ÇáÃæá

    //Property Set
    void SetLastName(string LastName) // æÙíİÉ áÊÚííä ÇáÇÓã ÇáÃÎíÑ
    {
        _LastName = LastName; // ÊÚííä ÇáÇÓã ÇáÃÎíÑ
    }

    //Property Get
    string GetLastName() // æÙíİÉ ááÍÕæá Úáì ÇáÇÓã ÇáÃÎíÑ
    {
        return _LastName; // ÅÑÌÇÚ ÇáÇÓã ÇáÃÎíÑ
    }

    __declspec(property(get = GetLastName, put = SetLastName)) string LastName; // ÎÇÕíÉ ááÍÕæá æÊÚííä ÇáÇÓã ÇáÃÎíÑ

    //Property Set
    void SetEmail(string Email) // æÙíİÉ áÊÚííä ÇáÈÑíÏ ÇáÅáßÊÑæäí
    {
        _Email = Email; // ÊÚííä ÇáÈÑíÏ ÇáÅáßÊÑæäí
    }

    //Property Get
    string GetEmail() // æÙíİÉ ááÍÕæá Úáì ÇáÈÑíÏ ÇáÅáßÊÑæäí
    {
        return _Email; // ÅÑÌÇÚ ÇáÈÑíÏ ÇáÅáßÊÑæäí
    }
    __declspec(property(get = GetEmail, put = SetEmail)) string Email; // ÎÇÕíÉ ááÍÕæá æÊÚííä ÇáÈÑíÏ ÇáÅáßÊÑæäí

    //Property Set
    void SetPhone(string Phone) // æÙíİÉ áÊÚííä ÑŞã ÇáåÇÊİ
    {
        _Phone = Phone; // ÊÚííä ÑŞã ÇáåÇÊİ
    }

    //Property Get
    string GetPhone() // æÙíİÉ ááÍÕæá Úáì ÑŞã ÇáåÇÊİ
    {
        return _Phone; // ÅÑÌÇÚ ÑŞã ÇáåÇÊİ
    }
    __declspec(property(get = GetPhone, put = SetPhone)) string Phone; // ÎÇÕíÉ ááÍÕæá æÊÚííä ÑŞã ÇáåÇÊİ

    // æÙíİÉ ÊÑÌÚ ÇáÇÓã ÇáßÇãá
    string FullName()
    {
        return _FirstName + " " + _LastName; // ÅÑÌÇÚ ÇáÇÓã ÇáßÇãá
    }

};
