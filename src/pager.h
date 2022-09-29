#ifndef Pager_h
#define Pager_h

extern Pager* pager_open(const char* filename);
extern void db_close(Table* table);
extern void* get_page(Pager* pager, uint32_t page_num);
extern void pager_flush(Pager* pager, uint32_t page_num, uint32_t size);

#endif
