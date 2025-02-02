#include <iostream>
#include <windows.h>  // For playing sound on Windows
#include <random>
using namespace std;
class Account
{
private:
	                       //complex hash constants (k values)
const unsigned int k[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

    // Actual
    string username;
    string salt="";
    string pepper="";
    string hashedpassword;        // Variables for storing Hashed Values
    string hashedplace;
    string hashedfood;
    string hasheddate;
    bool Enabled=1;
    // Testing
    string input;
    char Ch;
    //LinkedList Variables
    struct Node
    {
    	Node *next;
    	string Username;
    	string Salt="";
    	string Pepper="";
    	int key;
    	string password;                    //Variables for List
    	string date;
    	string place;
    	string food;
    	bool Enabled=1;
	};
    Node *head=nullptr;
    int currentkey=1;
    int K;

public:
    void SignUp()
    {
    	SecureZeroMemory(&salt[0], salt.size());
    	SecureZeroMemory(&pepper[0], pepper.size());
    	taken:system("cls");
        cout << "\n\t\t\tAccount SignUp\n";                                       //Account SignUp
        while (1)
        {
            cout << "\nUsername : ";
            getline(cin, username); 
            if(userexists())
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
            	PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            	cout<<"\n\t\tUsername already Taken\n";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
            	system("pause");
            	goto taken;
			}
            PasswordCheck(input);
            for (int i = 0; i < 32; ++i)                               //generating salt
        		salt += generateSecureRandomCharacter();
        	for (int i = 0; i < 32; ++i)                                    //generating pepper
        		pepper += generateSecureRandomCharacter();
            hashedpassword = complex_hash(input,salt,pepper,currentkey);
            SecureZeroMemory(&input[0], input.size());                 // Securely wipe memory after hashing
            wrong:;  
            system("cls");
            cout << "\n\t\t\tAccount SignUp\n";
            cout << "\nTo keep your account & data secured in case you forget your password  ";
            cout << "\nWe would like to ask some questions ";
            break;
        }
        while (1)
        {
            cout << "\n\t\tWould you like to proceed(y/n)";
            cin >> Ch;
            cin.ignore();  // To clear the buffer after reading a char input
            system("cls");
            if (Ch == 'y' || Ch == 'Y')
            {
                cout << "\n\t\t\tAccount SignUp\n";
                cout << "\nEnter your date of birth(D/M/Y) : ";
                getline(cin, input);  
                hasheddate = complex_hash(input,salt,pepper,currentkey);
                SecureZeroMemory(&input[0], input.size());         // Securely wipe memory after hashing

                cout << "\nEnter your favorite place : ";
                getline(cin, input);  
                hashedplace = complex_hash(input,salt,pepper,currentkey);
                SecureZeroMemory(&input[0], input.size());             // Securely wipe memory after hashing

                cout << "\nEnter your favorite food : ";
                getline(cin, input);  
                hashedfood = complex_hash(input,salt,pepper,currentkey);
                SecureZeroMemory(&input[0], input.size());  // Securely wipe memory after hashing
                Enabled=1;
            }
            else if (Ch == 'n' || Ch == 'N')
                Enabled=0;                             //if two factor is disabled
            else
                goto wrong;
            break;
        }
        cout<<"\n\t\tSignUp Complete !\n\n";
        PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
        system("pause");
        insertNode();
    }

    int Signin()
    {
    	char ch;
    	int i = 0;
        system("cls");
        cout << "\n\t\t\tSignin";                                  //SignIn
        int count = 0;
        char check;
        while (1)
        {
            cout << "\nUsername : ";
            getline(cin, username);  
            if(username=="Admin")                               //For Admin Purposes
            {  
            	cout<<"\nPassword : ";
            	cin>>input;
            	if(input=="@@@")
            	{
            		printlist();
	            	system("pause");
					return 0;	
				}
			}
            if (!searchuser())                               //Check if user exists
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
                PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                cout << "\nUser not found.";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
                continue;
            }
            	
            while (1)
		    {
                cout << "\nPassword : ";               
                getline(cin,input);
                if (complex_hash(input,salt,pepper,K) != hashedpassword)
                {
                	HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\nWrong Password.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    count++;
                    if (count >= 3)
                    {
                    	
                        cout << "\n\t\t\tForgot Password?(y/n)";
                        cin >> check;
                        cin.ignore();  // To clear the buffer after reading a char input
                    }
                    if (check == 'y' || check == 'Y')
                    {
                        Forgot();
                        return 0;
                    }
                    continue;
                }
                SecureZeroMemory(&input[0], input.size());
                break;
            }
            PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Access.wav"), NULL, SND_FILENAME | SND_SYNC);

            cout<<"\n\n\t\tAccess Granted ! \n\n"; 
            system("pause");
            
            system("cls");
            return 1;
        }
    }

    void Forgot()                                    //Function for authorization when user forgets password
    {
    	string date , place , food ;
        system("cls");
        if (Enabled)
        {
        	while (1)
            {
                cout << "\nEnter your date of birth(D/M/Y) : ";
                getline(cin, date);  
                cout << "\nEnter your favorite place : ";
                getline(cin, place);  
                cout << "\nEnter your favorite food : ";
                getline(cin, food);                          
                if (complex_hash(food,salt,pepper,K) == hashedfood && complex_hash(date,salt,pepper,K) == hasheddate && complex_hash(place,salt,pepper,K) == hashedplace)
                {
                	SecureZeroMemory(&date[0], date.size());      // Securely wipe memory after hashing
          		    SecureZeroMemory(&place[0], place.size());   // Securely wipe memory after hashing
            	    SecureZeroMemory(&food[0], food.size()); 
                    Change();
                    break;
                }
                else
                {
                	HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\n\t\tPrivate information doesn't match. Try Again.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    continue;
                }
            }
            
        }
        else
        {
        	PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
        	HANDLE console_color; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
            cout << "\n\t\tSorry you didn't provide us with the information while creating this account .";
            cout << "\n\t\tTherefore, we can't help you .\n\n\t";
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,10);
            system("pause");
        }
    }

    void Change()                                           //function for additional account services
    {
        int x;
        PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
        cout<<"\n\t\tAuthenticated ! \n\t\t";
        system("pause");
        while (1)
        {
            
            system("cls");
            cout << "\n\t\t\tAccount Recovery";
            cout << "\n\t\t\t1.Change Username";
            cout << "\n\t\t\t2.Change Password";
            cout << "\n\t\t\t3.Delete Account";
            cout << "\n\t\t\tChoose from (1-3)  ";
            cout << "\nReturn(R)";
            cout << "\n\t\tYou choose:";
            cin >> Ch;
            cin.ignore();  // To clear the buffer after reading a char input
            switch (Ch)
            {
            case '1':
            	system("cls");
            	again:;
            	cout<<"\n\t\tEnter new username : ";
            	input=username;
            	getline(cin,username);
            	if(userexists())
            	{
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            		cout<<"\n\t\tSorry , username already taken\n";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
            		system("pause");
            		goto again;
				}
            	updateuser();

            	cout << "\n\t\tYour username has been changed !";
            	PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);

                system("pause");
                break;
            case '2':
                system("cls");
                PasswordCheck(input);
                hashedpassword = complex_hash(input,salt,pepper,K);
                updatepass();
                SecureZeroMemory(&input[0], input.size());              // Securely wipe memory after hashing

                cout << "\n\t\tYour password has been changed !";
                PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);

                system("pause");
                break;
            case '3':
                system("cls");
                cout << "\n\t\tAre you sure you want to delete your account(y/n)?";
                cin >> Ch;
                cin.ignore();                             // To clear the buffer after reading a char input
                if (Ch == 'y' || Ch == 'Y')
                {
	                delnode();
	                SecureZeroMemory(&hashedpassword[0],hashedpassword.size());              // Securely wipe memory after hashing
	                SecureZeroMemory(&hasheddate[0], hasheddate.size());                    // Securely wipe memory after hashing
	                SecureZeroMemory(&hashedplace[0], hashedplace.size());                 // Securely wipe memory after hashing
	                SecureZeroMemory(&hashedfood[0], hashedfood.size()); 
	                SecureZeroMemory(&salt[0], salt.size()); 
	                SecureZeroMemory(&pepper[0],pepper.size());
	                K=0;
                    x = 1;
                    cout << "\n\t\tYour Account has been deleted !";
                    PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
                    system("pause");
                }
                break;
            case 'R':
            case 'r':
                x = 1;
                break;
            default:
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
                PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                cout << "\n\t\t\tInvalid command";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
                break;
            }
            if (x == 1)
                break;
        }
    }
    void insertNode()                                      //inserting Node to head function
{
	Node *newNode=new Node;
	newNode->Username=username;
	SecureZeroMemory(&username[0],username.size());
	newNode->Salt = salt;
	newNode->Pepper = pepper;
	newNode->key = currentkey++;
	SecureZeroMemory(&pepper[0],pepper.size());
    SecureZeroMemory(&salt[0],salt.size());
	newNode->next=nullptr;
	newNode->password=hashedpassword;
	SecureZeroMemory(&hashedpassword[0], hashedpassword.size());
	newNode->Enabled=Enabled;
	newNode->date=hasheddate;                                                //assigning values 
	newNode->food=hashedfood;
	newNode->place=hashedplace;
	SecureZeroMemory(&hasheddate[0], hasheddate.size());
	SecureZeroMemory(&hashedfood[0], hashedfood.size());                         //securley wiping
	SecureZeroMemory(&hashedplace[0], hashedplace.size());
	if(head==nullptr)
	{
		head=newNode;
		
	}
	else
	{
		Node *temp=head;
		while(temp->next!=nullptr)
		{
			temp=temp->next;
		}
		temp->next=newNode;
	}
	
	
}
void printlist()                                      //function to print List for understanding
{
	system("cls");
	cout<<"\n\t\tList Of Accounts : \n\n";
	if(head==nullptr)
	{
		cout<<"\n\t\tNo Accounts\n";
		
	}
	else
	{
		Node *temp=head;
			while(temp!=nullptr)
		{
			cout<<temp->key<<".\tUsername :  "<<temp->Username<<"\n\n\tSalt : "<<temp->Salt<<"\n\n\tPepper : "<<temp->Pepper;
			cout<<"\n\n\tPassword : "<<temp->password<<endl<<endl;
			temp=temp->next;
		}
	}
}
void delnode()
{
	Node *temp=head;
	Node *prev=nullptr;
	if(username==head->Username)
	{
		head=temp->next;
		delete temp;
		return;
	}
	while(temp != nullptr)
	{
		if(temp->Username==username)
		{
			prev->next=temp->next;
			delete temp;
			return;
		}
		prev=temp;
		temp=temp->next;
	}
	
	cout<<"\n\t\tTarget not found";
}
int searchuser()                                  //searching for user
{
    Node *temp = head;
    while (temp != nullptr) 
	{
      
        if (username == temp->Username) 
		{
			K=temp->key;
            pepper = temp->Pepper;
            salt = temp->Salt;
            hashedpassword = temp->password;
            Enabled=temp->Enabled;
            hasheddate=temp->date;
            hashedfood=temp->food;
            hashedplace=temp->place;
            return 1;  
        }
        temp = temp->next;  
    }
    return 0;  
}

int userexists()                                  //checking if userexits
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(username!=temp->Username)
		{	
			temp=temp->next;
			continue;
		}
		else
			return 1;
	}
	return 0;
}
void updatepass()                   //function to change password
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(username==temp->Username)
		{	
			temp->password=hashedpassword;
			return;
		}
		temp=temp->next;
	}
}
void updateuser()             //function to change username
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(input==temp->Username)
		{	
			temp->Username=username;
			return;
		}
		temp=temp->next;
	}
}
// Right rotate function
unsigned int rightRotate(unsigned int x, unsigned int n) 
{
    return (x >> n) | (x << (32 - n));
}

// Custom character set for final hash output
const string CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=<>?;:,.[]{}|`/\"' ";
                                                                                                
// Function to convert integer to a custom base (using CHARSET)
char intToCustomChar(unsigned int value) 
{
    return CHARSET[value % CHARSET.length()];
}

// Pad message with optional salt
vector<unsigned char> padMessage(const string &input) {
    // Start with the original input
    vector<unsigned char> padded(input.begin(), input.end());
    
    // Append a 0x80 byte (the "1" bit in padding)
    padded.push_back(0x80);

    // Pad with zeros until the message length is 448 mod 512
    while ((padded.size() * 8) % 512 != 448) 
        padded.push_back(0x00);

    // Append the original message length as a 64-bit big-endian integer
    unsigned long long bitLength = input.size() * 8;
    for (int i = 7; i >= 0; --i)
        padded.push_back((bitLength >> (i * 8)) & 0xFF);

    return padded;
}

// The main SHA-256 computation
// Main custom hash function
string complex_hash(const string &input, const string &salt, const string &pepper , int num) 
{
    string modifiedInput="";
	for(int i=0 ;i<=input.length() ; i++)
	{
		modifiedInput+=input[i];                          //Adding pepper to input
		modifiedInput+=pepper;
	}
    vector<unsigned char> padded = padMessage(modifiedInput);

    // Initializing the hash values
    unsigned int h[8] = 
	{
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Process the padded message in 512-bit blocks
    for (size_t i = 0; i < padded.size(); i += 64)
	 {
        vector<unsigned int> w(64);
        for (int t = 0; t < 16; ++t) 
		{
            w[t] = (padded[i + t * 4] << 24) | (padded[i + t * 4 + 1] << 16) |
                   (padded[i + t * 4 + 2] << 8) | padded[i + t * 4 + 3];
        }

        for (int t = 16; t < 64; ++t) 
		{
            unsigned int s0 = rightRotate(w[t - 15], 7) ^ rightRotate(w[t - 15], 18) ^ (w[t - 15] >> 3);
            unsigned int s1 = rightRotate(w[t - 2], 17) ^ rightRotate(w[t - 2], 19) ^ (w[t - 2] >> 10);
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        unsigned int a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], h_val = h[7];

        for (int t = 0; t < 64; ++t) 
		{
            unsigned int s1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            unsigned int ch = (e & f) ^ ((~e) & g);
            unsigned int temp1 = h_val + s1 + ch + k[t] + w[t];
            unsigned int s0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned int temp2 = s0 + maj;

            h_val = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_val;
    }

    // Combine the final hash value and convert to a string
    string hash_result;
    for (int i = 0; i < 8; ++i) 
	{
        hash_result += intToCustomChar(h[i] >> 24);
        hash_result += intToCustomChar(h[i] >> 16);
        hash_result += intToCustomChar(h[i] >> 8);
        hash_result += intToCustomChar(h[i]);
    }

	num=num%hash_result.length();                          //num % 32

	modifiedInput="";
	for(int i=0 ;i<=hash_result.length() ; i++)               
	{
		if(i==num)
			modifiedInput+=salt;                       //Adding Salt at specific position
		modifiedInput+=hash_result[i];
	}

    return 	modifiedInput;                               //returning result
}

void PasswordCheck(string &password) 
{
    bool upper = false;
    bool lower = false;
    bool symbols = false;
    bool goodLength = false;
    bool hasNumber = false;
    bool s_password = false;

    while (!s_password) 
	{
		cout << "\nPassword requirements:\n";
        cout << "- At least one uppercase letter\n";
        cout << "- At least one lowercase letter\n";
        cout << "- At least one special symbol (e.g., @, #, $, etc.)\n";
        cout << "- At least one numeric digit (0-9)\n";
        cout << "- At least 8 characters long\n\n";
        missed:;
        cout << "Enter a password : ";
       	getline(cin,password);
            
        // Reset the validation flags for each attempt
        upper = lower = symbols = goodLength = hasNumber = false;

        // Check each character of the password
        for (size_t i = 0; i < password.length(); i++) 
		{
            char c = password[i];
            if (isupper(c)) upper = true;
            if (islower(c)) lower = true;
            if (ispunct(c)) symbols = true;          // Checks for punctuation/symbols
            if (isdigit(c)) hasNumber = true;        // Checks for numeric digits
        }

        // Check the length requirement
        goodLength = (password.length() >= 8);

        // If all conditions are met, mark the password as strong
        
        if (upper && lower && symbols && goodLength && hasNumber) 
		{
            s_password = true;
            cout << "Strong password accepted.\n"; 
            system("pause");
        } 
		else 
		{
			system("cls");
			PlaySound(TEXT("C:/Users/hatim/OneDrive/Documents/User.wav"), NULL, SND_FILENAME | SND_SYNC);
			HANDLE console_color; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
            cout << "Weak password. Please try again.\n"; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,10);
            if (!upper) cout << "- Add at least one uppercase letter.\n";                                  //Conditions to be fulfilled
            if (!lower) cout << "- Add at least one lowercase letter.\n";
            if (!symbols) cout << "- Add at least one special symbol.\n";
            if (!hasNumber) cout << "- Add at least one numeric digit.\n";
            if (!goodLength) cout << "- Make the password at least 8 characters long.\n";
            goto missed;
        }
    }
}

// Function to generate a cryptographically secure random character
char generateSecureRandomCharacter() 
{

    const string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?`/\"' ";
         

    // Use random_device to get a cryptographically secure random number
    
    random_device rd;
    mt19937 gen(rd());              // Mersenne Twister generator
    uniform_int_distribution<> dis(0, allowedChars.size() - 1);

    // Randomly pick a character from the allowed list
    return allowedChars[dis(gen)];
}

};

int main()
{
    Account A;
    int ch ;
    HANDLE console_color; 
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color,10);
    while(1)
    {
	    cout<<"\n\t\tAccount Management System";                   //Account Management System
	    cout<<"\n\t\t1.SignUp";     
	    cout<<"\n\t\t2.SignIn";
	    cout<<"\n\t\t3.Exit";
	    cout<<"\n\t\tChoose from (1-3) : ";
	    cin>>ch;
	    cin.ignore();
	    switch(ch)
	    {
	    	case 1:
	    		A.SignUp();                          //Different Cases handled using switch
	    		system("cls");
	    		break;
	    	case 2:
	    		A.Signin();
	    		system("cls");
	    		break;
	    	case 3:
	    		return 0;
	    	default:
	    		system("cls");
	    		HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
	    		cout<<"\n\t\tInvalid Input"; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
	    		break;
		}
	}
}
