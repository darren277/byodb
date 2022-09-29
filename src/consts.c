

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

// TABLE DEFINITION
#define TABLE_MAX_PAGES 100


typedef struct {uint32_t id; char username[COLUMN_USERNAME_SIZE+1]; char email[COLUMN_EMAIL_SIZE+1];} Row;
typedef struct {int file_descriptor; uint32_t file_length; uint32_t num_pages; void* pages[TABLE_MAX_PAGES];} Pager;
typedef struct {uint32_t root_page_num; Pager* pager;} Table;
typedef struct {Table* table; uint32_t page_num; uint32_t cell_num; bool end_of_table;} Cursor;

// ROW DEFINITION
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t PAGE_SIZE = 4096;


