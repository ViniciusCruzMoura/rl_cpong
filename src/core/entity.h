#ifndef ENTITY_H
#define ENTITY_H

typedef struct CBall {
    float radius;
    Vector2 position;
    Vector2 speed;
} CBall;

typedef struct CPaddle {
    float speed;
    Rectangle rec;
} CPaddle;

typedef struct CMenuOption {
    char *label;
    Rectangle recs;
} CMenuOption;

typedef struct CMenu {
    CMenuOption option[5];
    int optionSelected;
    int mouseHoverRec;
} CMenu;

#endif // ENTITY_H