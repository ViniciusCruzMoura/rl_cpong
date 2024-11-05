#ifndef INIFILE_PARSER_H 
#define INIFILE_PARSER_H 

#define MAX_LINE_LENGTH 256

typedef struct KeyValue {
    char *key;
    char *value;
    struct KeyValue *next;
} KeyValue;

typedef struct Section {
    char *name;
    KeyValue *keyValues;
    struct Section *next;
} Section;

typedef struct IniFileConfig {
    Section *sections;
} IniFileConfig;

IniFileConfig *create_config();
void free_config(IniFileConfig *config);
void trim_whitespace(char *str);
void parse_ini_file(const char *filename, IniFileConfig *config);
const char* get_value_ini_file(IniFileConfig *config, const char *section, const char *key);
void display_all_ini_file(IniFileConfig *config);

#endif //INIFILE_PARSER_H
