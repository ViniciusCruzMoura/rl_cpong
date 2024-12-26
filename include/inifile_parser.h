#ifndef INIFILE_PARSER_H 
#define INIFILE_PARSER_H 

#define MAX_LINE_LENGTH 256

struct key_value {
    char *key;
    char *value;
    struct key_value *next;
};

struct section {
    char *name;
    struct key_value *keyValues;
    struct section *next;
};

struct ini_file_config {
    struct section *sections;
};

struct ini_file_config *create_config();
void free_config(struct ini_file_config *config);
void parse_ini_file(const char *filename, struct ini_file_config *config);
const char* get_value_ini_file(struct ini_file_config *config, const char *section, const char *key);
void display_all_ini_file(struct ini_file_config *config);

#endif //INIFILE_PARSER_H
