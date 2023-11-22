#include <bits/stdc++.h>

using namespace std;

class Gestor{
    private:
        string URL, password, username, notes, key, alphabet;

    public:
        Gestor(){
            URL = "";
            password = "";
            username = "";
            notes = "";
            alphabet = "abcdefghijklmnopqrstuvwxyz";
            key = "";
        }

        void createFile(){
            ifstream file;
            file.open("password.csv");
            if (!file)
            {
                ofstream File("password.csv");
                string url = "URL", user = "username", pass = "password", note = "notes";
                cypher(url, alphabet, key, url);
                cypher(user, alphabet, key, user);
                cypher(pass, alphabet, key, pass);
                cypher(note, alphabet, key, note);
                File << url << "," << user << "," << pass << "," << note << endl;
                File.close();
            }
        }

        void setURL(string URL){
            this->URL = URL;
        }
        string getURL(){
            return URL;
        }

        void setkey(string key){
            this->key = key;
        }
        string getkey(){
            return key;
        }

        void setusername(string username){
            this->username = username;
        }
        string getusername(){
            return username;
        }

        void setpassword(string password){
            this->password = password;
        }
        string getpassword(){
            return password;
        }

        void setnotes(string notes){
            this->notes = notes;
        }
        string getnotes(){
            return notes;
        }

        bool cypher(string input, string before, string key, string &output){
            output = "";

            if (before.size() != key.size())
            {
                return false;
            }

            for (int i = 0, n = input.size(); i < n; i++){
                int foundIndex = before.find(tolower(input[i]));

                if(foundIndex >= 0){
                    output += isupper(input[i]) ? toupper(key[foundIndex]) : key[foundIndex];
                }
                else{
                    output += input[i];
                }
            }
            return true;
        }

        bool encipher(string input, string &output){
            return cypher(input, alphabet, key, output);
        }

        bool decipher(string input, string &output){
            return cypher(input, key, alphabet, output);
        }

        void read(){
            ifstream File("password.csv");
            string tmp;
            while(getline(File, tmp)){
                decipher(tmp, tmp);
                cout << tmp << endl;
            }
            cout << endl;
            File.close();
        }

        void saveTofile(){
            ofstream File;
            File.open("password.csv", ios::app);
            string cypheredurl, cypheredusername, cypherednotes, cypheredpassword;
            cypher(URL, alphabet, key, cypheredurl);
            cypher(username, alphabet, key, cypheredusername);
            cypher(password, alphabet, key, cypheredpassword);
            cypher(notes, alphabet, key, cypherednotes);
            File << cypheredurl << "," << cypheredusername << "," << cypheredpassword << "," << cypherednotes << endl;
            File.close();
        }

        void search(string in){
            ifstream File("password.csv");
            string tmp;
            while(getline(File, tmp)){
                decipher(tmp, tmp);
                if (tmp.find(in) != tmp.npos){
                    cout << tmp << endl;
                }
            }
            File.close();
        }

        void supr(string target){
            ifstream File("password.csv");
            vector<string> vec;
            string tmp;
            while(getline(File, tmp))
            {
                string memento;
                decipher(tmp, memento);
                if(memento.find(target) != memento.npos){
                    continue;
                }
                else{
                    vec.push_back(tmp);
                } 
            }
            File.close();
            remove("password.csv");
            createFile();
            ofstream newFile;
            newFile.open("password.csv", ios::app);
            for(int i = 0, n = vec.size(); i < n; i++){
                newFile << vec[i] << endl;
            }
            newFile.close();
        }

        void printOptions(){
            cout << "Presione el numero de la opcion que desea" << endl;
            cout << "1. Mostrar el listado" << endl;
            cout << "2. Agregar una entrada" << endl;
            cout << "3. Buscar" << endl;
            cout << "4. Borrar" << endl;
            cout << "5. Salir" << endl;
        }
};


int main()
{
    Gestor passwords;
    string key;
    while (key.size() != 26)
    {
        cout << "Introduzca la llave de 26 digitos a continuacion: ";
        cin >> key;
    }
    passwords.setkey(key);
    //passwords.setkey("yhkqgvxfoluapwmtzecjdbsnri");
    passwords.createFile();
    
    int c = 0;
    while (c != 5)
    {
        passwords.printOptions();
        cin >> c;
        string s, tmp;

        switch (c)
        {
        case 2:
            cout << "URL: ";
            cin >> tmp;
            passwords.setURL(tmp);
            cout << "username: ";
            cin >> tmp;
            passwords.setusername(tmp);
            cout << "password: ";
            cin >> tmp;
            passwords.setpassword(tmp);
            cout << "Notas: ";
            getline(cin, tmp);
            getline(cin, tmp);
            passwords.setnotes(tmp);

            passwords.saveTofile();
            break;
        case 1:
            passwords.read();
            break;

        case 3:
            cout << "Escriba el URL del sitio que desea ver sus contrasenas: ";
            cin >> s;
            passwords.search(s);
            break;

        case 4:
            cout << "Escriba el usuario que desea borrar: ";
            cin >> s;
            passwords.supr(s);
            break;
        
        default:
            break;
        }
    }
    
    return 0;
}