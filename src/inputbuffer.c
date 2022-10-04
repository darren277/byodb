
typedef struct {char* buffer; size_t buffer_length; ssize_t input_length;} InputBuffer;

typedef enum { EXECUTE_SUCCESS, EXECUTE_DUPLICATE_KEY, EXECUTE_TABLE_FULL } ExecuteResult;
typedef enum { META_COMMAND_SUCCESS, META_COMMAND_UNRECOGNIZED_COMMAND } MetaCommandResult;
typedef enum { PREPARE_SUCCESS, PREPARE_STRING_TOO_LONG, PREPARE_SYNTAX_ERROR, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {StatementType type; Row row_to_insert; char* table_name;} Statement;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer, char* database) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}
