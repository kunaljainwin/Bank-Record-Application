// #include <iostream>
// #include <fstream>
// #include <cctype>
// #include <string>
// #include <iomanip>
// #include <regex>
// #include <limits.h>
#include <bits/stdc++.h>
// For Excel handling
// #include "libxl.h"//Not found
// Time
// #include<chrono>
// #include <ctime>

using namespace std;
/****************************************************************************

 //Class :       CAccount
 //Description:  It is collection of data regarding a Bank Management System.
 //              It consists various data members and methods which effectively generate
 //              a bank management system.

 //Remarks:      Added validations to all data types using Regex.

 //Last Modified By:  Abhishek Bedare (Trainee ODIN 63MTT01348)

 //Last Modified Date:  March 27, 2023

 ***************************************************************************/

class CAccount
{
public:
    int m_nAccountNumber;
    char m_strFirstName[10];
    char m_strLastName[10];
    float m_fSavingAccBalance;
    float m_fCurrentAccBalance;
    char m_cAccountType;
    char m_strMobileNumber[13];
    char m_strCityName[10];
    char m_strEmail[20];
    char m_strDematAccNumber[17];
    float m_fFixedDepositAmt;
    float m_fMedicalInsCover;
    float m_fMutualFundInvAmt;
    float m_fLifeInsPolicyCover[3] = {0};
    char m_strNominee[6][10] = {0};
    char m_strAccountStatus;
    char m_cLocker, m_cPassbook, m_cEStatement;

    static int m_snNextAccountNum;
    CAccount()
    {
        this->m_strAccountStatus = 'A';
        this->m_fFixedDepositAmt = 0;
        this->m_fMedicalInsCover = 0;
        this->m_fMutualFundInvAmt = 0;
        strcmp(this->m_strCityName, "");
        strcmp(this->m_strDematAccNumber, "");
        strcmp(this->m_strEmail, "");
        strcmp(this->m_strFirstName, "");
        strcmp(this->m_strLastName, "");
        strcmp(this->m_strMobileNumber, "");
        this->m_fSavingAccBalance = 0;
        this->m_fCurrentAccBalance = 0;
        this->m_cAccountType = 'S';
        this->m_cLocker = 'N';
        this->m_cPassbook = 'N';
        this->m_cEStatement = 'N';
        this->m_nAccountNumber = 0;
        this->m_strAccountStatus = 'A';
        // memset(this->m_strNominee, 0, sizeof(this->m_strNominee)); // initialize the array
        // initialize the array
    };

    void CreateAccount();
    void ShowAccount() const;
    void Modify();
    void CloseAccount();
    void Deposit(int);
    void Withdraw(int);
    void Report() const;
    float GetAccountBalance() const;
    char GetAccountType() const;
    char GetAccountStatus() const;
    float ValidateAmount(float);
    bool IsValidMobileNumber(string);
    bool IsValidName(string);
    bool IsValidEmail(string);
    bool IsValidDematAccNumber(string);
    static void SetLastAccountNumber(long m_nAccountNumber);
    int GetAccountNumber() const;
    // static int GetLastAccountNumber();
};

void ImportRecords();
void ExportRecords();

int CAccount::m_snNextAccountNum = 1;

bool CAccount::IsValidMobileNumber(string strMobileNumber)
{

    const regex pattern("(0|91)?[6-9][0-9]{9}");

    if (regex_match(strMobileNumber, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CAccount::IsValidName(string strName)
{

    const regex pattern("[a-zA-Z]{2,20}");

    if (regex_match(strName, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CAccount::IsValidEmail(string strEmail)
{

    const regex pattern("[a-zA-Z0-9]+[.|'']?[a-zA-Z0-9]+@[a-zA-Z]+.com");

    if (regex_match(strEmail, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CAccount::IsValidDematAccNumber(string strDematAccNumber)
{

    const regex pattern("(IN|[0-9]{2})[0-9]{14}");

    if (regex_match(strDematAccNumber, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}
float CAccount::ValidateAmount(float fNumber)
{
    bool lbFlagForNumberTesting = false;
    do
    {
        cout << "\nEnter Here Rs: ";
        cin >> fNumber;
        if (cin.fail())
        {
            cout << "Error....enter numeric value only\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {

            if (GetAccountType() == 'S' && fNumber < 1000)
            {
                cout << "Amount should be at least Rs 1000.\n";
            }
            else if (GetAccountType() == 'C' && fNumber < 5000)
            {
                cout << "Amount should be at least Rs 5000.\n";
            }
            else
            {
                lbFlagForNumberTesting = true;
            }
        }

    } while (!lbFlagForNumberTesting);

    return fNumber;
}
void CAccount::SetLastAccountNumber(long nValue)
{
    m_snNextAccountNum = nValue;
}
// int CAccount::GetLastAccountNumber()
// {
//  return m_snNextAccountNum;
// }

// ofstream &operator<<(ofstream &ofs, CAccount &acc)
// {
//  ofs << acc.m_nAccountNumber << endl;

//  return ofs;
// }
// CAccount::CAccount()
// {
//     //m_snNextAccountNum++;
//     // m_nAccountNumber=m_snNextAccountNum;
// }
void CAccount::CreateAccount()
{
    m_nAccountNumber = m_snNextAccountNum++;
    char lcNomineeName[15];
    int lnChoice;
    float lfSwapper;
    int lnNomineeCount = 0, lnNomineeCount2 = 0, lnLifeInsPolicyCount = 0;
    char lcFlagForNominee = 'y', lcFlagforLifeIns = 'y';

    cout << "\n\nEnter the First Name of the Account holder : ";
    // cin.ignore();
    // getline(cin,m_strFirstName);
    cin >> m_strFirstName;
    while (!IsValidName(m_strFirstName))
    {
        cout << "Name should have alphabets only and length in range 2-20.";
        cout << "\nFirst Name: ";
        cin >> m_strFirstName;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter the Last Name of the Account holder : ";
    cin >> m_strLastName;
    while (!IsValidName(m_strLastName))
    {
        cout << "Name should have alphabets only and length in range 2-20.";
        cout << "\nLast Name: ";
        cin >> m_strLastName;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        cout << "\nEnter Type of the Account (C/S) : ";
        cin >> m_cAccountType;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (m_cAccountType == 'C' || m_cAccountType == 'c' || m_cAccountType == 'S' || m_cAccountType == 's')
        {
            m_cAccountType = toupper(m_cAccountType);
            break;
        }
        cout << "Please enter C/S only.";
    }   
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nPlease Enter Initial Account Balance\nMin Balance for Saving Account: Rs 1000.";
    cout << "\nMin Balance for Current Account: Rs 5000.";
    if (GetAccountType() == 'S')
    {
        m_fSavingAccBalance = ValidateAmount(m_fSavingAccBalance);
         cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        m_fCurrentAccBalance = 0;
    }
    else
    {
        m_fCurrentAccBalance = ValidateAmount(m_fCurrentAccBalance);
        cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        m_fSavingAccBalance = 0;
    }

    cout << "\nEnter Your City Name: ";
    cin >> m_strCityName;
    while (!IsValidName(m_strCityName))
    {
        cout << "Plase enter a valid City Name: ";
        cin >> m_strCityName;
         cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
   

    cout << "\nEnter Your Mobile Number : ";
    cin >> m_strMobileNumber;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (!IsValidMobileNumber(m_strMobileNumber))
    {
        cout << "Please enter a valid mobile number: ";
        cin >> m_strMobileNumber;
         cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nEnter Your Email: ";
    cin >> m_strEmail;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (!IsValidEmail(m_strEmail))
    {
        cout << "Enter a valid email: ";

        cin >> m_strEmail;
    }

    cout << "\n\nCongratulations! Your Account is Successfully Created!!";
    cout << "\nYour Account No. is: " << m_nAccountNumber;
    cout << "\nKeep this for future reference.";

    do
    {
        cout << "\n\nPlease choose suitable option for addtional services.";

        cout << "\n1.Locker Facility";
        cout << "\n2.Passbook";
        cout << "\n3.eStatement";
        cout << "\n4.Fixed Deposit";
        cout << "\n5.Medical Insurance";
        cout << "\n6.Life Insurance";
        cout << "\n7.Nomination";
        cout << "\n8.Mutual Fund";
        cout << "\n9.Add Demat Account";
        cout << "\n10.EXIT";
        cout << "\nYour Choice: ";
        cin >> lnChoice;
        switch (lnChoice)
        {
        case 1:

            while (true)
            {
                cout << "\nDo you want to avail Locker facility? (Y/N): ";
                cin >> m_cLocker;
               cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (m_cLocker == 'Y' || m_cLocker == 'y' || m_cLocker == 'N' || m_cLocker == 'n')
                {
                    cout << "\nYour request for locker facility has been approved.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 2:
            while (true)
            {
                cout << "\nDo you want to avail Passbook facility? (Y/N): ";
                cin >> m_cPassbook;

                if (m_cPassbook == 'Y' || m_cPassbook == 'y' || m_cPassbook == 'N' || m_cPassbook == 'n')
                {
                    cout << "\nYour request for Passbook has been approved.\nYou will recieve your passbook within 5 working days.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 3:
            while (true)
            {
                cout << "\nDo you want to avail eStatement facility? (Y/N): ";
                cin >> m_cEStatement;

                if (m_cEStatement == 'Y' || m_cEStatement == 'y' || m_cEStatement == 'N' || m_cEStatement == 'n')
                {
                    cout << "\nYour request for eStatement has been approved.\nYour account statement will be emailed to you soon.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 4:
            cout << "\nPlease Enter an Amount for Fixed Deposit";
            m_fFixedDepositAmt = ValidateAmount(m_fFixedDepositAmt);
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTransaction successful. Your request is approved!";
            cout << "\nFixed Deposit of Rs " << m_fFixedDepositAmt << " has been created for A/C " << m_nAccountNumber;
            break;
        case 5:
            cout << "\nPlease Enter Medical Insurance Coverage Plan Amount";
            m_fMedicalInsCover = ValidateAmount(m_fMedicalInsCover);
           cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTransaction successful. Your request is approved!";
            cout << "\nYou are insured under medical insurance coverage of RS" << m_fMedicalInsCover;
            break;
        case 6:
            cout << "\nPlease enter amount of Life Insurance Policy Cover.\nYou can enter maximum 3 covers.\n";

            while (lnLifeInsPolicyCount < 3 && (lcFlagforLifeIns == 'y' || lcFlagforLifeIns == 'Y'))
            {

                cout << "Amount for Policy " << lnLifeInsPolicyCount + 1 << " ";
                cout << ":Rs ";
                // cin>> lfSwapper;

                m_fLifeInsPolicyCover[lnLifeInsPolicyCount] = ValidateAmount(lfSwapper);
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (lnLifeInsPolicyCount == 2)
                {
                    cout << "\nYou have successfully added 3 Life Insurance Policy Covers.";
                    break;
                }
                cout << "\nDo you want to add more?(Y/N) ";
                cin >> lcFlagforLifeIns;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                lnLifeInsPolicyCount++;
            }

            break;
        case 7:

            cout << "\nPlease enter names of Nominee for your account.\nYou can have maximum 3 nominees.\n";

            while (lnNomineeCount2 < 3 && (lcFlagForNominee == 'y' || lcFlagForNominee == 'Y'))
            {

                cout << "Nominee" << lnNomineeCount2 + 1 << " ";
                cout << "\nEnter First Name ";
                cin >> lcNomineeName;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!IsValidName(lcNomineeName))
                {
                    cout << "Name should have alphabets only and length in range 2-20.";
                    cout << "\nFirst Name: ";
                    cin >> lcNomineeName;
                     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                strcpy(m_strNominee[lnNomineeCount], lcNomineeName);

                cout << "\nEnter Last Name ";
                cin >> lcNomineeName;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!IsValidName(lcNomineeName))
                {
                    cout << "Name should have alphabets only and length in range 2-20.";
                    cout << "\nLast Name: ";
                    cin >> lcNomineeName;
                     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                strcpy(m_strNominee[lnNomineeCount + 1], lcNomineeName);
                if (lnNomineeCount2 == 2)
                {
                    cout << "\nYou have successfully added 3 Nominees\n";
                    break;
                }

                cout << "\nDo you want to add more?(Y/N) ";
                cin >> lcFlagForNominee;

                lnNomineeCount += 2;
                lnNomineeCount2++;
            }
            break;
        case 8:

            cout << "\nPlease Enter an Amount To Invest in our Star Mutual Fund";
            m_fMutualFundInvAmt = ValidateAmount(m_fMutualFundInvAmt);
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nTransaction Successful. Your Request is Approved!";
            cout << "\nYou have Successfully Invested an Amount of RS " << m_fMutualFundInvAmt << " in Star Mutual Fund ";
            break;
        case 9:

            cout << "\nPlase Provide Your Demat Accout Number.";
            cout << "\nFor CDSL: 16 digit numric \nFor NSDL: 16 character starting with “IN” followed by a 14-digit numeric code";
            cout << "\nEnter here:";
            cin >> m_strDematAccNumber;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!IsValidDematAccNumber(m_strDematAccNumber))
            {
                cout << "Enter a Valid Demat Account Number: ";
                cin >> m_strDematAccNumber;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 10:

            cout << "\n\nWait....";
            cout << "\n\nPress Enter to Return Back to Main Menu";
            break;
        default:
            cout << "Invalid Choice";
        }

    } while (lnChoice != 10);
}

void CAccount::ShowAccount() const
{
    Report();
}

void CAccount::Modify()

{
    int lnChoice;
    char lcNomineeName[15];
    float lfSwapper = 0, lfAmtForFD, lfAmtForFD2, lfAmtForMF, lfAmtForMF2;
    int lnNomineeCount = 0, lnNomineeCount2 = 0, lnLifeInsPolicyCount = 0;
    char lcTempForAccType, lcFlagForNominee = 'y', lcFlagforLifeIns = 'y';
    int lnChoiceForFD, lnChoiceForMF;

    do
    {
        cout << "\n\nPlease choose suitable option for Modification";
        cout << "\n1.Locker Facility";
        cout << "\n2.Passbook";
        cout << "\n3.eStatement";
        cout << "\n4.Update Fixed Deposit";
        cout << "\n5.Medical Insurance";
        cout << "\n6.Life Insurance";
        cout << "\n7.Update Nominee";
        cout << "\n8.Mutual Fund";
        cout << "\n9.Update Demat Account";
        cout << "\n10.Update Account Type";
        cout << "\n11.Change City Name";
        cout << "\n12.Update Mobile Number";
        cout << "\n13.Update Email";
        cout << "\n14.EXIT";
        cout << "\nYour Choice: ";
        cin >> lnChoice;
        switch (lnChoice)
        {
        case 1:

            while (true)
            {
                cout << "\nUpdate your choice for locker.\nDo you want to avail Locker facility? (Y/N): ";
                cin >> m_cLocker;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (m_cLocker == 'Y' || m_cLocker == 'y' || m_cLocker == 'N' || m_cLocker == 'n')
                {
                    cout << "\nYour request for locker facility has been approved.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 2:
            while (true)
            {
                cout << "\nUpdate your choice for passbook.\nDo you want to avail Passbook facility? (Y/N): ";
                cin >> m_cPassbook;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (m_cPassbook == 'Y' || m_cPassbook == 'y' || m_cPassbook == 'N' || m_cPassbook == 'n')
                {
                    cout << "\nYour request for Passbook has been approved.\nYou will recieve your passbook within 5 working days.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 3:
            while (true)
            {
                cout << "\nUpdate your choice for eStatment.\nDo you want to avail eStatement facility? (Y/N): ";
                cin >> m_cEStatement;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (m_cEStatement == 'Y' || m_cEStatement == 'y' || m_cEStatement == 'N' || m_cEStatement == 'n')
                {
                    cout << "\nYour request for eStatement has been approved.\nYour account statement will be emailed to you soon.";
                    break;
                }
                cout << "\nPlease enter Y/N only";
            }
            break;
        case 4:
            cout << "\nPlease Choose from Following for Transaction Related to Fixed Deposit.";
            cout << "\n1.Add Amount to FD\n2.Withdraw Amount from FD\n3.Close FD\n";
            cout << "Your Choice: ";
            cin >> lnChoiceForFD;
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (lnChoiceForFD == 1)
            {

                cout << "\nPlase Enter an Amount for Investing More in Your Fixed Deposit.";
                m_fFixedDepositAmt += ValidateAmount(lfAmtForFD);
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');                cout << "\nTransaction Successful. Your request is approved!";
                cout << "\nUpdated FD Balance: " << m_fFixedDepositAmt;
            }
            else if (lnChoiceForFD == 2)
            {
                cout << "\nPlease Enter Amount to Withdraw from Your Fixed Deposit Account.";
                lfAmtForFD2 = ValidateAmount(lfAmtForFD);
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');                if (lfAmtForFD2 <= m_fFixedDepositAmt)
                {
                    m_fFixedDepositAmt -= lfAmtForFD2;
                    cout << "\nTransaction successful. Your request is approved!\nUpdated FD Balance: " << m_fFixedDepositAmt;
                }
                else
                {
                    cout << "\nTransaction Failed.\nInsufficent Amount in FD.";
                }
            }
            else if (lnChoiceForFD == 3)
            {
                cout << "\nPlease Collect Your FD Amount Rs" << m_fFixedDepositAmt << "from Cashier.";
                m_fFixedDepositAmt = 0;
                cout << "\nTransaction Successful. Your Request is Approved!\nUpdated FD Balance: " << m_fFixedDepositAmt;
            }
            else
            {
                cout << "\nInvalid Choice";
            }
            break;
        case 5:

            cout << "\nPlease enter updated Medical Insurance Coverage amount: Rs";

            m_fMedicalInsCover = ValidateAmount(m_fMedicalInsCover);
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTransaction successful. Your request is approved!";
            cout << "\nYour new medical insurance coverage: RS" << m_fMedicalInsCover;
            break;
        case 6:
            cout << "\nPlease enter amount of Life Insurance Policy Cover.\nIn case you do not want to modify, please re-enter your previous amount\nYou can enter maximum 3 covers.\n";

            while (lnLifeInsPolicyCount < 3 && (lcFlagforLifeIns == 'y' || lcFlagforLifeIns == 'Y'))
            {

                cout << "Amount for Policy " << lnLifeInsPolicyCount + 1 << " ";

                m_fLifeInsPolicyCover[lnLifeInsPolicyCount] = ValidateAmount(lfSwapper);
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (lnLifeInsPolicyCount == 2)
                {
                    cout << "\nYou have successfully added 3 Life Insurance Policy Covers.";
                    break;
                }
                cout << "\nDo you want to add more?(Y/N) ";
                cin >> lcFlagforLifeIns;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                lnLifeInsPolicyCount++;
            }

            break;
        case 7:

            cout << "\nPlease enter updated names of Nominee for your account.\nYou can have maximum 3 nominees.\n";

            while (lnNomineeCount2 < 3 && (lcFlagForNominee == 'y' || lcFlagForNominee == 'Y'))
            {

                cout << "Nominee" << lnNomineeCount2 + 1 << " ";
                cout << "\nEnter First Name ";
                cin >> lcNomineeName;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!IsValidName(lcNomineeName))
                {
                    cout << "Name should have alphabets only and length in range 2-20.";
                    cout << "\nFirst Name: ";
                    cin >> lcNomineeName;
                     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                strcpy(m_strNominee[lnNomineeCount], lcNomineeName);
                cout << "\nEnter Last Name ";
                cin >> lcNomineeName;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!IsValidName(lcNomineeName))
                {
                    cout << "Name should have alphabets only and length in range 2-20.";
                    cout << "\nLast Name: ";
                    cin >> lcNomineeName;
                     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                strcpy(m_strNominee[lnNomineeCount + 1], lcNomineeName);
                if (lnNomineeCount2 == 2)
                {
                    cout << "\nYou have successfully added 3 Nominees\n";
                    break;
                }

                cout << "\nDo you want to add more?(Y/N) ";
                cin >> lcFlagForNominee;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                lnNomineeCount += 2;
                lnNomineeCount2++;
            }
            break;
        case 8:

            cout << "\nPlease choose from following for transaction related to Mutual Fund";
            cout << "\n1.Add amount to MF\n2.Withdraw amount from MF\n3.Close MF\n";
            cout << "Your Choice: ";
            cin >> lnChoiceForMF;
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (lnChoiceForMF == 1)
            {

                cout << "\nPlease enter amount to add to your Mutual Fund account";
                cin >> lfAmtForMF;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                m_fMutualFundInvAmt += ValidateAmount(lfAmtForMF);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nTransaction successful. Your request is approved!";

                cout << "\nUpdated MF Investment: Rs " << m_fMutualFundInvAmt;
            }
            else if (lnChoiceForMF == 2)
            {
                cout << "\nPlease enter amount to withdraw from your Mutual Fund Account";

                lfAmtForMF2 = ValidateAmount(lfAmtForMF);
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (lfAmtForMF2 <= m_fMutualFundInvAmt)
                {
                    m_fMutualFundInvAmt -= lfAmtForMF2;
                    cout << "\nTransaction Successful. Your request is approved!\nUpdated MF Balance: " << m_fMutualFundInvAmt;
                }
                else
                {
                    cout << "\nTransaction Failed.\nInsufficent amount in Mutual Fund";
                }
            }
            else if (lnChoiceForMF == 3)
            {
                cout << "\nPlease collect your MF amount Rs" << m_fMutualFundInvAmt << "from cashier";

                m_fMutualFundInvAmt = 0;
                cout << "\nTransaction successful. Your request is approved!\nUpdated MF Balance: " << m_fMutualFundInvAmt;
            }
            else
            {
                cout << "\nInvalid Choice";
            }

            break;
        case 9:
            cout << "\nUpdated Demat accout number";
            cout << "\nFor CDSL: 16 digit numric \nFor NSDL: 16 character starting with “IN” followed by a 14-digit numeric code";
            cout << "\nEnter here:";
            cin >> m_strDematAccNumber;
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!IsValidDematAccNumber(m_strDematAccNumber))
            {
                cout << "Enter a valid Demat Account Number: ";
                cin >> m_strDematAccNumber;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Your Demat account number has been successfully updated....";
            break;
        case 10:
            while (true)
            {
                cout << "\nUpdated Type of Account (C/S) : ";
                cin >> lcTempForAccType;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                lcTempForAccType = toupper(lcTempForAccType);
                if (lcTempForAccType == GetAccountType())
                {
                    cout << "Your Previous Account Type was the Same!";
                    continue;
                }
                if (lcTempForAccType == 'C' || lcTempForAccType == 'S')
                {
                    m_cAccountType = lcTempForAccType;
                    break;
                }
                cout << "Please enter C/S only.";
            }

            lfSwapper = m_fSavingAccBalance;
            m_fSavingAccBalance = m_fCurrentAccBalance;
            m_fCurrentAccBalance = lfSwapper;

            cout << "Your account type has been successfully updated....";
            break;
        case 11:

            cout << "\nUpdated City Name: ";
            cin >> m_strCityName;
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!IsValidName(m_strCityName))
            {
                cout << "Plase enter a valid City Name: ";
                cin >> m_strCityName;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');            cout << "Your city name has been successfully updated....";
            break;
        case 12:

            cout << "\nUpdated Mobile Number: ";
            cin >> m_strMobileNumber;
            while (!IsValidMobileNumber(m_strMobileNumber))
            {
                cout << "Please enter a valid mobile number: ";
                cin >> m_strMobileNumber;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Your Mobile Number has been Successfully Updated....";
            break;
        case 13:

            cout << "\nUpdated Email: ";
            cin >> m_strEmail;
             cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!IsValidEmail(m_strEmail))
            {
                cout << "Enter a valid email: ";

                cin >> m_strEmail;
                 cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Your email has been successfully updated....";
            break;
        case 14:

            cout << "\n\nWait....";
            cout << "\n\nPress Enter to return back to main menu";
            break;
        default:
            cout << "Invalid Choice";
        }

    } while (lnChoice != 14);
}
void CAccount::CloseAccount()
{
    cout << "\nAccount No. : " << m_nAccountNumber;
    cin.getline(m_strFirstName, 10);
    // getline(cin, m_strFirstName);
    m_fSavingAccBalance = 0;
    m_fCurrentAccBalance = 0;
    m_strAccountStatus = 'C';
    m_cLocker = 'n';
    m_cPassbook = 'n';
    m_cEStatement = 'n';
}

void CAccount::Deposit(int nAmount)
{
    if (GetAccountType() == 'S')
    {
        m_fSavingAccBalance += nAmount;
    }
    else
    {
        m_fCurrentAccBalance += nAmount;
    }
}

void CAccount::Withdraw(int nAmount)
{
    if (GetAccountType() == 'S')
    {
        m_fSavingAccBalance -= nAmount;
    }
    else
    {
        m_fCurrentAccBalance -= nAmount;
    }
}

void CAccount::Report() const
{

    cout << "---------------------------------------------------------------------------" << endl;
    cout << "A/c No.: " << m_nAccountNumber << "\nName of Account Holder: " << m_strFirstName << " " << m_strLastName
         << "\nA/c Status: " << m_strAccountStatus
         << "\nA/c Type: " << ((m_cAccountType == 'S' || m_cAccountType == 's') ? "Saving" : "Current")
         << "\nSaving A/c Balance: Rs " << m_fSavingAccBalance
         << "\nCurrent A/c Balance: Rs " << m_fCurrentAccBalance
         << "\nCity Name: " << m_strCityName
         << "\nMobile No: " << m_strMobileNumber << "\nEmail: " << m_strEmail
         << "\nLocker Opted?: " << ((m_cLocker == 'Y' || m_cLocker == 'y') ? "Opted" : "Not Opted")
         << "\nPassbook Opted?: " << ((m_cPassbook == 'Y' || m_cPassbook == 'y') ? "Opted" : "Not Opted")
         << "\nEstatement Opted?: " << ((m_cEStatement == 'Y' || m_cEStatement == 'y') ? "Opted" : "Not Opted")
         << "\nFixed Deposit Amount: Rs " << m_fFixedDepositAmt
         << "\nMedical Insurance coverage: Rs " << m_fMedicalInsCover
         << "\nAmount invested in Star Mutual Fund: Rs " << m_fMutualFundInvAmt
         << "\nRegistered Demat A/c No.: " << m_strDematAccNumber;
    cout << "\nLife insurance Policy Covers: \n";

    for (int lnItr = 0; lnItr < 3; lnItr++)
    {
        if (m_fLifeInsPolicyCover[lnItr] != 0)
        {

            cout << "Policy " << lnItr + 1 << ") Rs " << m_fLifeInsPolicyCover[lnItr] << "\n";
        }
    }
    int lnCount = 1;

    cout << "\nNominee Details: " << endl;

    for (int lnItr = 0; lnItr < 6 && m_strNominee[lnItr] != "0"; lnItr += 2)

    {

        cout << lnCount << ")" << m_strNominee[lnItr] << " " << m_strNominee[lnItr + 1] << "\n";
        lnCount++;
    }

    cout << "---------------------------------------------------------------------------" << endl;
    cout << "\n";
}

int CAccount::GetAccountNumber() const
{
    return m_nAccountNumber;
}

float CAccount::GetAccountBalance() const
{
    if (GetAccountType() == 'S')
    {
        return m_fSavingAccBalance;
    }
    else
    {
        return m_fCurrentAccBalance;
    }
}

char CAccount::GetAccountType() const
{
    return m_cAccountType;
}
char CAccount::GetAccountStatus() const
{
    return m_strAccountStatus;
}

void WriteRecordToFile();
void DisplayAccount();
void ModifyRecord(int);
void DeleteRecord(int);
void DisplayAllRecords();
void WithdrawBalance(int, int);
void AutoIncrement()
{
    CAccount ac;
    fstream inFile;
    inFile.open("bank.bin", ios::binary | ios::in);
    if (!inFile)
    {

        cout << "No previous records found  !! Press any Key...";
        return;
    }
    // last object

    inFile.seekg(-1 * (int)sizeof(CAccount), ios::end);
    inFile.read(reinterpret_cast<char *>(&ac), sizeof(CAccount));
    ac.SetLastAccountNumber(ac.GetAccountNumber() + 1);
    // inFile.seekg(sizeof(CAccount));
    // inFile.read(reinterpret_cast<char *>(&ac), sizeof(CAccount))
    cout << "Next account no. is " << ac.m_snNextAccountNum << endl;
    // cout<<ac.m_nAccountNumber;

    inFile.close();
}
int main()
{
    try
    {
        // Block of code to try
        AutoIncrement();
    }
    catch (exception &e)
    {
        // Error handling
        cout << "Error occured";
    }

    int lcChoice; // updated by kunal to int for more options in menu
    int lnNumber;
    do
    {

        cout << "\n***************************************" << endl;
        cout << "       WELCOME TO STAR BANK      \n";
        cout << "***************************************" << endl;
        cout << "Please choose an option to proceed" << endl;

        cout << "\n1. OPEN NEW ACCOUNT";
        cout << "\n2. DEPOSIT AMOUNT";
        cout << "\n3. WITHDRAW AMOUNT";
        cout << "\n4. ACCOUNT DETAILS";
        cout << "\n5. DISPLAY ALL RECORDS";
        cout << "\n6. CLOSE AN ACCOUNT";
        cout << "\n7. MODIFY AN ACCOUNT";
        // Modified by Kunal
        cout << "\n8. IMPORT";
        cout << "\n9. EXPORT";

        cout << "\n10. EXIT";
        // END
        cout << "\nYour Choice: ";

        cin >> lcChoice;

        switch (lcChoice)
        {
        case 1:
            WriteRecordToFile();
            break;
        case 2:

            cout << "\n\nEnter the account No. : ";
            cin >> lnNumber;
            WithdrawBalance(lnNumber, 1);
            break;
        case 3:

            cout << "\n\nEnter the account No. : ";
            cin >> lnNumber;
            WithdrawBalance(lnNumber, 2);
            break;
        case 4:

            DisplayAccount();
            break;
        case 5:
            DisplayAllRecords();
            break;
        case 6:

            cout << "\n\nEnter the account No. : ";
            cin >> lnNumber;
            DeleteRecord(lnNumber);
            break;
        case 7:

            cout << "\n\nEnter the account No. : ";
            cin >> lnNumber;
            ModifyRecord(lnNumber);
            break;
        // Added by Kunal
        case 8:

            ImportRecords();
            break;

        case 9:
            ExportRecords();
            break;

        case 10:

            cout << "\n\nThanks for using our Services.\nHave a nice day!";
            break;
        // END
        default:
            cout << "Invalid Option";
            break;
        }
        cin.ignore();
        cin.get();
    } while (lcChoice != 10);
    return 0;
}

void WriteRecordToFile()
{

    CAccount ac;
    fstream outFile;

    outFile.open("bank.bin", ios::out | ios::binary | ios::app);
    // cout<<"size of object"<<sizeof(ac)<<endl;
    // cout<<"size of class"<<sizeof(CAccount)<<endl;

    // cout <<"\nBefore CreateAccount():"<< ac.GetAccountNumber() << endl;

    ac.CreateAccount();
    cout << "\nNext account number will be:" << ac.GetAccountNumber()+1<< endl;
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(CAccount));
    outFile.close();
}

void DisplayAccount()
{
    CAccount lCAccount;
    bool lbFlag = false;
    int lnNumber;
    do
    {
        cout << "1 . Search with account number" << endl;
        cout << "2 . Search with account holder name" << endl;
        cout << "3 . Search with account holder mobile number" << endl;
        cout << "4 . Search with account holder email id" << endl;
        cin >> lnNumber;
    } while (lnNumber > 4 || lnNumber < 1);

    if (lnNumber == 1)
    {

        cout << "\n\n\tEnter The account No. : ";
        int lnAccountNumber;
        cin >> lnAccountNumber;

        fstream inFile;
        inFile.open("bank.bin", ios::in | ios::binary);

        if (!inFile)
        {
            cout << "File could not be open !! Press any Key...";
            return;
        }
        cout << "\nBALANCE DETAILS\n";
        while (inFile.read(reinterpret_cast<char *>(&lCAccount), sizeof(CAccount)))
        {
            if (lCAccount.GetAccountNumber() == lnAccountNumber)
            {
                lCAccount.Report();
                lCAccount.GetAccountType() == 'S' ? cout << "Your Saving Account balance is RS " << lCAccount.GetAccountBalance()
                                                  : cout << "Your Current Account balance is RS " << lCAccount.GetAccountBalance();

                lbFlag = true;
            }
        }
        inFile.close();
        if (lbFlag == false)
            cout << "\n\n\t\t\tAccount number does not exist";
    }
    else
    {
        cout << "\n\n\tEnter The account holder name or mobile number or email: ";
        char lnAccountDetail[20];
        scanf_s("%s", lnAccountDetail);

        fstream inFile;
        inFile.open("bank.bin", ios::in | ios::binary);
        if (!inFile)
        {
            cout << "File could not be open !! Press any Key...";
            return;
        }
        cout << "\nBALANCE DETAILS\n";
        while (inFile.read(reinterpret_cast<char *>(&lCAccount), sizeof(CAccount)))
        {
            // optimize this code
            if (strcmp(lCAccount.m_strFirstName, lnAccountDetail) == 0 || strcmp(lCAccount.m_strLastName, lnAccountDetail) == 0 || strcmp(lCAccount.m_strEmail, lnAccountDetail) == 0)
            {
                lCAccount.Report();
                lCAccount.GetAccountType() == 'S' ? cout << "Your Saving Account balance is RS " << lCAccount.GetAccountBalance()
                                                  : cout << "Your Current Account balance is RS " << lCAccount.GetAccountBalance();

                lbFlag = true;
            }
        }
        inFile.close();
        if (lbFlag == false)
            cout << "\n\n\t\t\tAccount number does not exist";
    }
}

void ModifyRecord(int nNumber)
{
    bool lfFound = false;
    CAccount ac;
    fstream File;
    File.open("bank.bin", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    while (!File.eof() && lfFound == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(CAccount));
        if (ac.GetAccountNumber() == nNumber)
        {
            ac.ShowAccount();
            cout << "\nEnter The New Details of account" << endl;
            ac.Modify();
            int lnPos = (-1) * static_cast<int>(sizeof(CAccount));
            File.seekp(lnPos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(CAccount));
            cout << "\nRecord Updated";
            lfFound = true;
        }
    }
    File.close();
    if (lfFound == false)
        cout << "\n\nRecord Not Found ";
}

void DeleteRecord(int nNumber)
{

    bool lfFound = false;
    CAccount ac;
    fstream File;
    File.open("bank.bin", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && lfFound == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(CAccount));
        if (ac.GetAccountNumber() == nNumber)
        {
            ac.ShowAccount();

            ac.CloseAccount();
            int lnPos = (-1) * static_cast<int>(sizeof(CAccount));
            File.seekp(lnPos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(CAccount));
            cout << "\nWe regret you do not like our services....\n";
            cout << "\nAs per your request your account is closed.\nPlase Collect your account balance from the cashier.\n";
            lfFound = true;
        }
    }
    File.close();
    if (lfFound == false)
        cout << "\nRecord Not Found ";
}

void DisplayAllRecords()
{
    CAccount ac;
    fstream inFile;
    inFile.open("bank.bin", ios::in | ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n**************** All Accounts Record *********************\n\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(CAccount)))
    {
        ac.Report();
    }
    cout << "\nPress enter to return to main menu.";
    inFile.close();
}

void WithdrawBalance(int nNumber, int nOption)
{
    int lnAmount;
    bool lfFound = false;
    CAccount ac;
    fstream File;
    File.open("bank.bin", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    while (!File.eof() && lfFound == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(CAccount));
        if (ac.GetAccountNumber() == nNumber)
        {
            ac.ShowAccount();
            if (nOption == 1)
            {

                cout << "\n\nEnter the amount to be deposited: ";
                cin >> lnAmount;
                ac.Deposit(lnAmount);
                cout << "\nRs" << lnAmount << " has been deposited in your account.";
            }
            if (nOption == 2)
            {

                cout << "\n\nEnter The amount to withdraw: ";
                cin >> lnAmount;
                int lnBal = ac.GetAccountBalance() - lnAmount;
                if (lnBal < 0)
                    cout << "Error....Insufficient Balance.";
                else
                {
                    ac.Withdraw(lnAmount);
                    cout << "\nRs" << lnAmount << " has been withdrawn from your account.";
                }
            }
            int lnPos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(lnPos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(CAccount));
            cout << "\n\nRecord Updated";
            lfFound = true;
        }
    }
    File.close();
    if (lfFound == false)
        cout << "\n\nRecord Not Found ";
}

// Added by Kunal
// requirements
// 1. Import records from csv, xlsx, txt
// 2. Export records to csv, xlsx, txt, pdf
// 3. Search records
// 4. Add color to the console output
// Usage:
// SetColor(10); => green text line
// SetColor(7); => white text line

void ImportRecords()
{
    // csv
    // xlsx
    // txt
    puts("Keep file in same directory as the executable file");
    string lstrTemp = "";
    cout << "Enter CSV file name without extension to import: ";
    cin >> lstrTemp;
     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    fstream lImportCSVFile(lstrTemp+".csv", ios::in);
    if (!lImportCSVFile)
    {
        cout << "CSV File could not be opened !! Press any Key...";
        return;
    }
    else
    {
        string s;

        getline(lImportCSVFile, s, '\n'); // remove header row

        while (getline(lImportCSVFile, s, '\n'))
        {
            CAccount lCAccount;
            stringstream lSS(s);

            string lTemp;
            getline(lSS, lTemp, ',');
            // lCAccount.m_nAccountNumber =lCAccount.GetAccountNumber();
            // cout<<CAccount::m_snNextAccountNum<<endl;
            lCAccount.m_nAccountNumber = lCAccount.m_snNextAccountNum++;
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strFirstName, lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strLastName, lTemp.c_str());
            getline(lSS, lTemp, ',');
            lCAccount.m_fSavingAccBalance = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fCurrentAccBalance = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_cAccountType = lTemp[0];
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strMobileNumber, lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strCityName, lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strEmail, lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strDematAccNumber, lTemp.c_str());
            getline(lSS, lTemp, ',');
            lCAccount.m_fFixedDepositAmt = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fMedicalInsCover = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fMutualFundInvAmt = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fLifeInsPolicyCover[0] = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fLifeInsPolicyCover[1] = stof(lTemp);
            getline(lSS, lTemp, ',');
            lCAccount.m_fLifeInsPolicyCover[2] = stof(lTemp);
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[0], lTemp.c_str());

            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[1], lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[2], lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[3], lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[4], lTemp.c_str());
            getline(lSS, lTemp, ',');
            strcpy(lCAccount.m_strNominee[5], lTemp.c_str());
            getline(lSS, lTemp, ',');
            lCAccount.m_strAccountStatus = lTemp[0]; // char
            getline(lSS, lTemp, ',');
            lCAccount.m_cLocker = lTemp[0];
            getline(lSS, lTemp, ',');
            lCAccount.m_cPassbook = lTemp[0];
            getline(lSS, lTemp, ',');
            lCAccount.m_cEStatement = lTemp[0];
            fstream outFile;

            outFile.open("bank.bin", ios::out | ios::binary | ios::app);
            outFile.write(reinterpret_cast<char *>(&lCAccount), sizeof(CAccount));
            outFile.close();
        }
        // // Read from csv
        // // Create and fill object

        // // Fill object
        // // Write to binary

        lImportCSVFile.close();
        puts("Records imported successfully");
        // fstream out("bank.bin", ios::out | ios::binary);
    }
}
void ExportRecords()
{
    // csv
    // xlsx
    // txt
    // pdf
    //
    // Read all binary
    fstream lFStarBank;
    lFStarBank.open("bank.bin", ios::in | ios::binary);
    fstream lExportFile;
    // create csv file
    remove("export.csv");
    lExportFile.open("export.csv", ios::out | ios::trunc);

    // loop through all records
    CAccount lCAccount;
    lExportFile << "Account Number,First Name,Last Name,Saving Account Balance,Current Account Balance,Account Type,Mobile Number,City Name,Email Address,Demat Account Number,Fixed Deposit,Medical Insurance Cover,Mutual Fund Investment Amount,Cover0,Cover1,Cover2,Nominee0,Nominee1,Nominee2,Nominee3,Nominee4,Nominee5,Account Status,Locker,Passbook,E Statement";
    lExportFile << endl;
    while (lFStarBank.read(reinterpret_cast<char *>(&lCAccount), sizeof(CAccount)))
    {
        // Write to csv
        lExportFile << lCAccount.m_nAccountNumber;
        lExportFile << ',';
        lExportFile << lCAccount.m_strFirstName;
        lExportFile << ',';
        lExportFile << lCAccount.m_strLastName;
        lExportFile << ',';
        lExportFile << lCAccount.m_fSavingAccBalance;
        lExportFile << ',';
        lExportFile << lCAccount.m_fCurrentAccBalance;
        lExportFile << ',';
        lExportFile << lCAccount.m_cAccountType;
        lExportFile << ',';
        lExportFile << lCAccount.m_strMobileNumber;
        lExportFile << ',';
        lExportFile << lCAccount.m_strCityName;
        lExportFile << ',';
        lExportFile << lCAccount.m_strEmail;
        lExportFile << ',';
        lExportFile << lCAccount.m_strDematAccNumber;
        lExportFile << ',';
        lExportFile << lCAccount.m_fFixedDepositAmt;
        lExportFile << ',';
        lExportFile << lCAccount.m_fMedicalInsCover;
        lExportFile << ',';
        lExportFile << lCAccount.m_fMutualFundInvAmt;
        lExportFile << ',';
        lExportFile << lCAccount.m_fLifeInsPolicyCover[0];
        lExportFile << ',';
        lExportFile << lCAccount.m_fLifeInsPolicyCover[1];
        lExportFile << ',';
        lExportFile << lCAccount.m_fLifeInsPolicyCover[2];
        lExportFile << ',';
        lExportFile << lCAccount.m_strNominee[0];

        lExportFile << ',';

        lExportFile << lCAccount.m_strNominee[1];
        lExportFile << ',';
        lExportFile << lCAccount.m_strNominee[2];
        lExportFile << ',';
        lExportFile << lCAccount.m_strNominee[3];
        lExportFile << ',';
        lExportFile << lCAccount.m_strNominee[4];
        lExportFile << ',';
        lExportFile << lCAccount.m_strNominee[5];
        lExportFile << ',';
        lExportFile << lCAccount.m_strAccountStatus;
        lExportFile << ',';
        lExportFile << lCAccount.m_cLocker;
        lExportFile << ',';
        lExportFile << lCAccount.m_cPassbook;
        lExportFile << ',';
        lExportFile << lCAccount.m_cEStatement;
        lExportFile << '\n';
    }
    // save csv
    lFStarBank.close();
    lExportFile.close();
}
// string GetSystemTime()
// {
//     // Get current time
//     time_t now = time(0);
//     // Convert now to tm struct for local timezone
//     tm *ltm = localtime(&now);
//     // Print various components of tm structure.

//     // cout << "Time: " << 1 + ltm->tm_hour << ":";
//     // cout << 1 + ltm->tm_min << ":";
//     // cout << 1 + ltm->tm_sec << endl;
//     return ltm->tm_mday+"-"+to_string(1 + ltm->tm_mon)+"-"+to_string(1900 + ltm->tm_year);
// }
// End
