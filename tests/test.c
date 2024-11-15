#include "rlcpong.h"

#define TEST_ASSERT(cond, expected_value) \
    do { \
        if (cond) { \
            printf("PASS| %s(): Expected '%s' - Test Passed\n", __func__, expected_value); \
        } else { \
            printf("^^^^^FAIL| %s(): Expected '%s' - Test Failed\n", __func__, expected_value); \
        } \
    } while (0)

size_t total_entities = 0;

void test_entity_create()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    TEST_ASSERT(e->m_tag == ENTITY_TYPE_PLAYER, "entity tag should be same");
    for (size_t i = 0; i < 128000; ++i) {
        entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    }
    for (size_t i = 0; i < 128000; ++i) {
        entity_create(&e, ENTITY_TYPE_ITEM, ++total_entities);
    }
    size_t count = entity_size(e);
    TEST_ASSERT(count >= 256000, "should have than 256000 entities");
}

void test_entity_search_by_tag()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    
    e = entity_search_by_tag(e, ENTITY_TYPE_PLAYER);
    TEST_ASSERT(e->m_tag == ENTITY_TYPE_PLAYER, "entity tag should be same");

    size_t count = entity_size(e);
    TEST_ASSERT(count == 2, "should have 2 entities with player tag");
}

void test_entity_search_by_id()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);

    size_t tst_id = entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities)->m_id;
    e = entity_search_by_id(e, tst_id);
    TEST_ASSERT(e != NULL, "shouldn't be NULL pointer");
    TEST_ASSERT(e->m_id == tst_id, "entity id should be same");
    TEST_ASSERT(e->m_tag == ENTITY_TYPE_NOTHING, "entity tag should be same");
}

void test_entity_remove_by_id()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    size_t tst_id = entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities)->m_id;
    entity_remove_by_id(&e, tst_id);
    e = entity_search_by_id(e, tst_id);
    TEST_ASSERT(e == NULL, "should be NULL pointer");
}

void test_entity_remove_by_tag()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);

    entity_remove_by_tag(&e, ENTITY_TYPE_PLAYER);
    e = entity_search_by_tag(e, ENTITY_TYPE_PLAYER);
    size_t count = entity_size(e);
    TEST_ASSERT(count == 0, "should have 0 entities with player tag");
} 

void test_entity_append()
{
    Entity *e = NULL;
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);

    Entity *e2 = NULL;
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    
    size_t first_el_size = entity_size(e);
    size_t second_el_size = entity_size(e2);
    entity_append(&e, e2);
    size_t end_size = entity_size(e);
    TEST_ASSERT(first_el_size+second_el_size == end_size, "should append 2 entities list");
}

void test_ini_file_parser()
{
    IniFileConfig *conf = create_config();
    parse_ini_file("tests/test_conf.ini", conf);
    const char* x = get_value_ini_file(conf, "Section", "key");
    const char* y = get_value_ini_file(conf, "Section", "text");
    //display_all_ini_file(conf);
    TEST_ASSERT(strcmp(y, "text with spaces") == 0, "should parser a 'text with spaces'");
    TEST_ASSERT(strcmp(x, "value") == 0, "should parser an ini file");
    free_config(conf);
}

void tests_run()
{
    test_ini_file_parser();
    test_entity_create();
    test_entity_search_by_tag();
    test_entity_search_by_id();
    test_entity_remove_by_id();
    test_entity_remove_by_tag();
    test_entity_append();
}
