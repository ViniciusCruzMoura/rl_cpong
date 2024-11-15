#include "rlcpong.h"

IniFileConfig *create_config() {
    IniFileConfig *config = (IniFileConfig *)malloc(sizeof(IniFileConfig));
    config->sections = NULL;
    return config;
}

void free_config(IniFileConfig *config) {
    Section *sec = config->sections;
    while (sec) {
        KeyValue *kv = sec->keyValues;
        while (kv) {
            KeyValue *tempKV = kv;
            kv = kv->next;
            free(tempKV->key);
            free(tempKV->value);
            free(tempKV);
        }
        Section *tempSec = sec;
        sec = sec->next;
        free(tempSec->name);
        free(tempSec);
    }
    free(config);
}

void parse_ini_file(const char *filename, IniFileConfig *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }

    Section *currentSection = NULL;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        //trim_whitespace
        char *trim_str = line;
        char *trim_end;
        while (isspace((unsigned char)*trim_str)) trim_str++;
        if (*trim_str != 0) {
            trim_end = trim_str + strlen(trim_str) - 1;
            while (trim_end > trim_str && isspace((unsigned char)*trim_end)) trim_end--;
            *(trim_end + 1) = '\0';
        }

        if (line[0] == '\0' || line[0] == ';') continue; // Skip empty lines and comments
        if (line[0] == '[') { // Section header
            char *end = strchr(line, ']');
            if (end) {
                *end = '\0';
                Section *newSection = (Section *)malloc(sizeof(Section));
                newSection->name = strdup(line + 1); // Skip the '['
                newSection->keyValues = NULL;
                newSection->next = config->sections;
                config->sections = newSection;
                currentSection = newSection;
            }
        } else if (currentSection) { // Key-value pair
            char *equals = strchr(line, '=');
            if (equals) {
                *equals = '\0';
                KeyValue *newKV = (KeyValue *)malloc(sizeof(KeyValue));
                newKV->key = strdup(line);
                newKV->value = strdup(equals + 1);
                newKV->next = currentSection->keyValues;
                currentSection->keyValues = newKV;
            }
        }
    }
    fclose(file);
}

const char* get_value_ini_file(IniFileConfig *config, const char *section, const char *key) {
    Section *current_sec = config->sections;
    // Find the specified section
    while (current_sec) {
        if (strcmp(current_sec->name, section) == 0) {
            KeyValue *current_pair = current_sec->keyValues;
            // Find the specified key
            while (current_pair) {
                if (strcmp(current_pair->key, key) == 0) {
                    return current_pair->value; // Return the value
                }
                current_pair = current_pair->next;
            }
            break; // Key not found in this section
        }
        current_sec = current_sec->next;
    }
    return NULL; // Section or key not found
}

void display_all_ini_file(IniFileConfig *config) {
    for (Section *sec = config->sections; sec != NULL; sec = sec->next) {
        printf("[%s]\n", sec->name);
        for (KeyValue *kv = sec->keyValues; kv != NULL; kv = kv->next) {
            printf("%s = %s\n", kv->key, kv->value);
        }
    }
}
