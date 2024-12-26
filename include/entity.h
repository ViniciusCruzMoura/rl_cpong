#ifndef ENTITY_H
#define ENTITY_H

typedef struct CFlags {
    bool is_visible;
    bool has_collided;
    bool is_circle;
    bool is_rectangle;
} CFlags;

typedef struct CShape {
    float radius;
    Rectangle rec;
    Color color;
} CShape;

typedef struct CCollision {
    float radius;
    Rectangle rec;
} CCollision;

typedef struct CScore {
    uint32_t value;
} CScore;

typedef struct CTransform {
    Vector2 pos;
    Vector2 velocity;
    float angle;
    float rotation;
    Vector2 scale;
} CTransform;

typedef struct CLifespan {
    uint32_t remaining_life;
    uint32_t total_life;
} CLifespan;

typedef struct CAnimation {
    bool loop;
    //sprite
} CAnimation;

enum entity_types
{
    ENTITY_TYPE_NOTHING = 0,
    ENTITY_TYPE_OBJECT,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM,
};

struct entity {
    struct entity *next;
    bool m_active;
    size_t m_id;
    enum entity_types m_tag;
    CFlags flags;
    CLifespan lifespan;
    CScore score;
    CAnimation animation;
    CCollision collision;
    CTransform transform;
    CShape shape;
};

uint32_t entity_size(struct entity *head);
struct entity *entity_create(struct entity **head, enum entity_types tag, size_t id);
struct entity *entity_search_by_tag(struct entity *head, enum entity_types tag);
struct entity *entity_search_by_id(struct entity *head, size_t id);
void entity_remove_by_id(struct entity **head, size_t id);
void entity_remove_by_tag(struct entity **head, enum entity_types tag);
struct entity *entity_append(struct entity **head1, struct entity *head2);
void entity_display(struct entity *head);
void entity_free(struct entity *head);

#endif //ENTITY_H
