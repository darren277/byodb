// PREPARE INSERT FUNCTION FOR STRING LENGTH CHECK

char *split(char *str, const char *delim)
{
    char *p = strstr(str, delim);

    if (p == NULL) return NULL;     // delimiter not found

    *p = '\0';                      // terminate string after head
    return p + strlen(delim);       // return tail substring
}


PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
  statement->type = STATEMENT_INSERT;

  char* keyword = strtok(input_buffer->buffer, " ");
  char* id_string = strtok(NULL, " ");
  char* username = strtok(NULL, " ");
  char* email = strtok(NULL, " ");
  
  if (id_string == NULL || username == NULL || email == NULL) {
    return PREPARE_SYNTAX_ERROR;
  }

  int id = atoi(id_string);
  if (strlen(username) > COLUMN_USERNAME_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }
  if (strlen(email) > COLUMN_EMAIL_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }

  statement->row_to_insert.id = id;
  strcpy(statement->row_to_insert.username, username);
  strcpy(statement->row_to_insert.email, email);

  return PREPARE_SUCCESS;
}



PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    statement->table_name = split(input_buffer->buffer, " INTO ");
    //printf("table_name: %s\n", statement->table_name);
    int args_assigned = sscanf(input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id), statement->row_to_insert.username, statement->row_to_insert.email);
    if (args_assigned < 3) {return PREPARE_SYNTAX_ERROR;}
    return prepare_insert(input_buffer, statement);
  }
  if (strncmp(input_buffer->buffer, "select", 6) == 0) {
    statement->type = STATEMENT_SELECT;
    statement->table_name = split(input_buffer->buffer, " FROM ");
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

