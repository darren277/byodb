
char* concat(const char *s1, const char *s2)
{
    const char *joiner;
    joiner = "-";

    const char *fileext;
    fileext = ".db";

    char *result = malloc(strlen(s1) + 1 + strlen(s2) + 3 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, joiner);
    strcat(result, s2);
    strcat(result, fileext);
    return result;
}

ExecuteResult execute_insert(Statement* statement, char* database) {
  char* filename = concat(database, statement->table_name);
  Table* table = db_open(filename);
  free(filename);

  void* node = get_page(table->pager, table->root_page_num);
  uint32_t num_cells = (*leaf_node_num_cells(node));

  Row* row_to_insert = &(statement->row_to_insert);
  uint32_t key_to_insert = row_to_insert->id;
  Cursor* cursor = table_find(table, key_to_insert);

  if (cursor->cell_num < num_cells) {
    uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
    if (key_at_index == key_to_insert) {return EXECUTE_DUPLICATE_KEY;}
  }
  
  leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

  free(cursor);

  db_close(table);

  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, char* database) {
  // extract table name from statement
  char* filename = concat(database, statement->table_name);
  printf("filename: %s\n", filename);
  Table* table = db_open(filename);
  //free(filename);

  Cursor* cursor = table_start(table);
  Row row;

  while (!(cursor->end_of_table)) {
     deserialize_row(cursor_value(cursor), &row);
     print_row(&row);
     cursor_advance(cursor);
   }

  free(cursor);

  db_close(table);
  
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, char* database) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
        return execute_insert(statement, database);
    case (STATEMENT_SELECT):
        return execute_select(statement, database);
  }
}

