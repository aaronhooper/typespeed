const char *to_bool_string(int b) {
  static const char *true_s = "true";
  static const char *false_s = "false";
  return b == 0 ? true_s : false_s;
}
