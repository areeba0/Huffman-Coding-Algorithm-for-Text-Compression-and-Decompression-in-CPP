#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct node 
{
    char data;
    int frequency;
    node* left;
    node* right;
};

struct queue_node
{
    node* data;
    queue_node* next;
};

class queue

{
private:
    queue_node* front;
    queue_node* rear;

public:
    queue() 
    {
         front = NULL;
         rear  = NULL;
    }

    ~queue() 
    {
        while (!is_empty()) 
        {
            dequeue();
        }
    }

    void enqueue(node* n)
    {
        queue_node* new_node = new queue_node;
        new_node->data = n;
        new_node->next = NULL;

        if (is_empty())
        {
            front = rear = new_node;
        } 
        else if (!is_empty()) 
        {
            rear->next = new_node;
            rear = new_node;
        }
    }

    node* dequeue()
    {
        if (is_empty()) 
        {
            return NULL;
        } 
        
        else if (front->next == NULL)
        {
            queue_node* temp = front;
            node* data = temp->data;

            front = rear = NULL;
            delete temp;

            return data;
        } 
        
        else
        {
            queue_node* temp = front;
            node* data = temp->data;

            front = front->next;
            delete temp;

            return data;
        }
    }

    bool is_empty() const 
    {
        if (front == NULL) 
        {
            return true;
        } 
        else if (front->next == NULL)
        {
            return false;
        } 
        else 
        {
            return false;
        }
    }

    queue_node* get_front() const 
    {
        if (front == NULL)
        {
            return NULL;
        } 
        else if (front->next == NULL)
        {
            return front;
        } 
        else 
        {
            return front;
        }
    }
};

class huffman_tree
{
     
private:

    node* root;
    std::string codes[256];

    node* create_node(char data, int frequency)
    {
        node* new_node = new node;
        new_node->data = data;
        new_node->frequency = frequency;
        new_node->left = new_node->right = nullptr;
        
        return new_node;
    }

    void delete_node(node* n) 
    {
        if (n) 
        {
            delete_node(n->left);
            delete_node(n->right);
            delete n;
        }
    }

    void build_tree(const std::string& input_filename) 
    {
        const int char_range = 256;
        int frequencies[char_range] = {0};

        ifstream input_file(input_filename);
        if (input_file.is_open())
        {
            char c;
            do
            {
                while (input_file.get(c))
                {
                    frequencies[static_cast<unsigned char>(c)]++;
                }
            } while (false);

            input_file.close();
        }
        else if (!input_file.is_open())
        {
            cout << "Unable to open file" << endl;
            return;
        }

        queue q;
        int i = 0;
        do {
            if (frequencies[i] > 0) 
            {
                node* new_node = create_node(static_cast<char>(i), frequencies[i]);
                q.enqueue(new_node);
            }
            ++i;
        } while (i < char_range);

        do {
            if (!q.is_empty() && q.get_front()->next != NULL)
            {
                queue_node* front_node = q.get_front();
                node* new_node = create_node('\0', 0);
                new_node->left = q.dequeue();
                new_node->right = q.dequeue();
                new_node->frequency = new_node->left->frequency + new_node->right->frequency;
                q.enqueue(new_node);
            }
        } while (!q.is_empty() && q.get_front()->next != NULL);

        root = q.dequeue();
    }

    void assign_codes(node* n, const std::string& code)
    {
        if (n)
        {
            if (n->data != '\0')
            {
                cout << n->data << ": " << code <<endl;
                
                codes[static_cast<unsigned char>(n->data)] = code;
            }
            assign_codes(n->left, code + "0");
            assign_codes(n->right, code + "1");
        }
    }

    void write_codes_to_file(const std::string& output_filename)
    {
        ofstream codes_file(output_filename);

        if (codes_file.is_open())
        {
            int i = 0;
            do {
                if (!codes[i].empty()) 
                {
                    codes_file << static_cast<char>(i) << " " << codes[i] << endl;
                }
                ++i;
            } while (i < 256);
            codes_file.close();
        } 
        else
        {
            cout << "Unable to open codes file" << endl;
        }
    }

public :

    huffman_tree() 
    {
         root = nullptr;
    }
        

    ~huffman_tree() 
    {
        delete_node(root);
    }

    node* get_root() const 
    {
        return root;
    }

    void build_and_assign_codes(const std::string& input_filename, const std::string& codes_filename) 
    {
         
        build_tree(input_filename);
        assign_codes(root, "");
        write_codes_to_file(codes_filename);
        
    }

    void encode_text(const std::string& input_filename) 
    {
        ifstream input_file(input_filename);
        ofstream encoded_file("encoded.txt", ios::binary);

        if (input_file.is_open())
        {
            if (encoded_file.is_open()) 
            {
                char c;
                do 
                {
                    while (input_file.get(c)
                    ) {
                        encoded_file << codes[static_cast<unsigned char>(c)];
                    }

                    input_file.close();
                    encoded_file.close();
                } while (false);
            } 
            else if (!encoded_file.is_open()) 
            {
                cout << "error!!! Unable to open encoded file. " << endl;
            }
        } else {
            std::cout << "error!!! Unable to open input file." << endl;
        }
    }

    void read_codes_from_file(const std::string& codes_filename) 
    {
        ifstream codes_file(codes_filename);

        bool file_open = codes_file.is_open();

        do {
            if (!file_open) 
            {
                cout << "Error!!! Unable to open codes file" << endl;
                break;
            }

            char character;
            string code;

            while (codes_file >> character >> code) 
            {
                codes[static_cast<unsigned char>(character)] = code;
            }

        } while (false);

        codes_file.close();
    }

    void decode_text(const std::string& input_filename, const std::string& output_filename)
    {
        read_codes_from_file("codes.txt");
        
        ifstream input_file(input_filename);
        ofstream decoded_file(output_filename);

        bool files_open = input_file.is_open() && decoded_file.is_open();

        do {
            if (!files_open)
            {
                cout << "Unable to open files" << endl;
                break;
            }

            string encoded_text;
            input_file >> encoded_text;

            string decoded_text;
            string current_code;

            char bit;
            size_t i = 0;
            while (i < encoded_text.size())
            {
                current_code += encoded_text[i];

                size_t j = 0;
                while (j < 256) 
                {
                    if (codes[j] == current_code) 
                    {
                        decoded_text += static_cast<char>(j);
                        current_code = "";
                        break;
                    }
                    ++j;
                }

                ++i;
            }

            decoded_file << decoded_text;
            cout << "Decoded text: " << decoded_text << endl;

        } while (false);

        input_file.close();
        decoded_file.close();
    }

    void decode_text_and_show(const string& input_filename, const string& output_filename)
    {
        read_codes_from_file("codes.txt");
        
        ifstream input_file(input_filename);
        ofstream decoded_file(output_filename);

        if (input_file.is_open() && decoded_file.is_open()) 
        {
            string encoded_text;
            input_file >> encoded_text;

            string decoded_text;
            string current_code;

            cout << "Code\t = \tLetter" << endl;

            char bit;
            size_t i = 0;
            do {
                current_code += encoded_text[i];

                size_t j = 0;
                while (j < 256) 
                {
                    if (codes[j] == current_code)
                    {
                        decoded_text += static_cast<char>(j);
                        cout << current_code << "\t\t" << static_cast<char>(j) << std::endl;
                        current_code = "";
                        break;
                    }
                    ++j;
                }

                ++i;
            } while (i < encoded_text.size());

            decoded_file << decoded_text;
            cout << "\nDecoded text: " << decoded_text << endl;

            input_file.close();
            decoded_file.close();
        } 
        else 
        {
            cout << "Unable to open files" << std::endl;
        }
    }

    void draw_tree(node* n, int depth = 0, char branch = ' ') 
    {
        const int indentation = 4;

        if (n) 
        {
            cout << std::setw(indentation * depth) << branch << "[" << n->data;
            if (n->data != '\0')
            {
                cout << " (" << codes[static_cast<unsigned char>(n->data)] << ")";
            }
            cout << "]" << std::endl;

            draw_tree(n->left, depth + 1, ' ');
            draw_tree(n->right, depth + 1, ' ');
        }
    }
};

int main() {
    cout << "*****------------------------------*****" << endl;
    cout << "              Huffman Coding            " << endl;
    cout << "*****------------------------------*****" << endl;
    huffman_tree ht;

    // Sender program
    ht.build_and_assign_codes("input.txt", "codes.txt");
    cout << "----------------------------------------" << endl;
    // Draw the Huffman tree
    cout << "Huffman Tree:" << endl;
    ht.draw_tree(ht.get_root());
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Encoded file has been generated successfully!!" << endl;
    cout << "-------------------------------------------------" << endl;
    ht.encode_text("input.txt");

    // Receiver program
    cout << "\nDecoding..." << endl;
    cout << "----------------------------------------" << endl;
    ht.decode_text_and_show("encoded.txt", "decoded.txt");

    return 0;
}
