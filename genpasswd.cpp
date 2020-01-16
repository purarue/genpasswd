#include <cctype>     // tolower
#include <cstdlib>    // getenv, exit, srand, rand
#include <iostream>   // cout, cerr, endl
#include <optional>   // optional
#include <string>     // string
#include <string.h>   // strcpy
#include <sstream>    // stringstream
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // getopt

const char* usage_str =
    "Yet another Password Generator\n\n"
    "usage:\n"
    "   genpasswd\n"
    "   genpasswd PASSWD_LENGTH\n"
    "   genpasswd [-n PASSWD_LENGTH] [-r CHARACTER_SET] [-c COUNT] [-p|-s]\n\n"
    "options:\n"
    "   -n N     length of password to generate\n"
    "   -c C     number of passwords to generate\n"
    "   -r R     character set to remove from allowed characters\n"
    "   -p       shorthand for -n 4 -r lower -r upper -r sym\n"
    "            to generate a string of random numbers of length 4\n"
    "            meant to be used for bank pins\n"
    "   -s       shorthand for -n 16 -r sym\n"
    "            meant for websites which have strict limits on passwords\n\n"
    "character sets:\n"
    "   lowercase   : l, lower, lowercase\n"
    "   uppercase   : u, upper, uppercase\n"
    "   numbers     : n, num, number, numbers\n"
    "   symbols     : s, sym, symbol, symbols\n\n"
    "examples:\n"
    "   genpasswd 40              : password of length 40\n"
    "   genpasswd -n 30 -rsym     : password of length 30 without symbols\n"
    "   genpasswd -p              : generate a bank pin\n\n"
    "Type genpasswd -h for help\n";

/**
 * Gets the environment variable 'envvar' as an integer
 * or defaults to 'def_val'
 */
int get_env_or(const std::string& envvar, const int def_val) {
  if (const char* def_val_str = std::getenv(envvar.c_str())) { // if environment variable exists
    try {
      if (const int parsed_int = std::stoi(def_val_str)) {
        if (parsed_int > 0) {
          return parsed_int;
        }
      }
    } catch (...) {
      fprintf(stderr, "Error converting '%s' to an integer, using default: %d\n",
              def_val_str, def_val);
    }
  }
  return def_val;
}

/**
 * Uses stoi to parse from 'char* s' to the optional
 * Does nothing if parsing fails
 * Checks to make sure int isn't negative, to validate unsigned int
 */
void parse_int(std::optional<unsigned int>& length_arg, const char* s) {
  try {
    if (const int parsed_int = std::stoi(s)) {
      if (parsed_int > 0) {
        length_arg = parsed_int;
      }
    }
  } catch (...) {
    fprintf(stderr, "Error converting '%s' to an integer.\n", s);
  }
}


/*
 * Given the allowed_character_sets array (bool[4]),
 * returns the allowed character domain
 * Each is 26 characters long to attempt to get equal distribution
 */
char* generate_domain(const bool* allowed_character_sets) {
  std::stringstream ss;
  if (allowed_character_sets[0]) {
    ss << "abcdefghijklmnopqrstuvwxyz";
  }
  if (allowed_character_sets[1]) {
    ss << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  }
  if (allowed_character_sets[2]) {
    ss << "00123456789012345678924685";
  }
  if (allowed_character_sets[3]) {
    ss << "!#$%&()*+,-./<=>?@[]^_`{}~";
  }
  char *d = new char[ss.str().size() + 1];
  strcpy(d, ss.str().c_str());
  return d;
}

/**
 * Sets 'pw' to a password of length 'n', randomly picking from 'domain'
 * uses rand() seeded with the current time in ms
 */
void generate_password(char* pw, const char* domain,
                       const int domain_length, const unsigned int length) {
  for (unsigned int i = 0; i < length; i++) {
    pw[i] = domain[rand() % domain_length];
  }
}

/*
 * Parse environment variables, command line arguments,
 * then call function with options to generate password
 */
int main(int argc, char *argv[]) {

  // seed rand with current time in milliseconds
  timeval t1;
  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);

  std::optional<unsigned int> length_arg; // length from user
  std::optional<unsigned int> count_arg;  // count from user

  // lowercase, uppercase, numbers, symbols
  bool allowed_character_sets[4] = {true, true, true, true};

  unsigned int default_passwd_length = get_env_or("GENPASSWD_LENGTH", 20);
  unsigned int default_simple_length = get_env_or("GENPASSWD_SIMPLE_LENGTH", 16);
  unsigned int default_pin_length = get_env_or("GENPASSWD_PIN_LENGTH", 4);
  unsigned int default_count = get_env_or("GENPASSWD_COUNT", 1);

  char fc; // first character, used to parse -r CHARACTER_SET
  int opt; // getopt opt

  // parse command line args
  while ((opt = getopt(argc, argv, ":n:c:r:ps")) != -1) {
    switch (opt) {
    case 'n':
      parse_int(length_arg, optarg);
      break;
    case 'c':
      parse_int(count_arg, optarg);
      break;
    case 'p':
      length_arg = default_pin_length;
      allowed_character_sets[0] = false;
      allowed_character_sets[1] = false;
      allowed_character_sets[3] = false;
      break;
    case 's':
      length_arg = default_simple_length;
      allowed_character_sets[3] = false;
      break;
    case 'r':
      // check what the user wants to ignore
      fc = tolower(optarg[0]); // first character can determine character set
      switch (fc) {
      case 'l':
        allowed_character_sets[0] = false;
        break;
      case 'u':
        allowed_character_sets[1] = false;
        break;
      case 'n':
        allowed_character_sets[2] = false;
        break;
      case 's':
        allowed_character_sets[3] = false;
        break;
      default:
        std::cerr << "Unrecognized character set: " << optarg << std::endl;
        std::cerr << usage_str;
        exit(1);
      }
      break;
    case '?':
    case 'h':
    default:
      std::cerr << usage_str;
      exit(1);
    }
  }

  // check for length as a positional argument
  // only set if user didn't already set the with the -n/-p/-s flag
  if (argc - optind > 0 && !length_arg) {
    parse_int(length_arg, argv[optind]);
  }

  // parse optional<int>'s
  unsigned int length = (length_arg) ? *length_arg : default_passwd_length;
  unsigned int count = (count_arg) ? *count_arg : default_count;

  // make sure at least one character set exists
  int character_sets = 0;
  for (int i = 0; i < 4; i++) {
    if (allowed_character_sets[i]) {
      character_sets++;
      // dont break so we can use the domain length later in generate_password
    }
  }
  int domain_length = character_sets * 26;
  if (character_sets == 0) {
    std::cerr << "At least one character set must exist." << std::endl;
    exit(1);
  }

  // generate domain
  char* domain = generate_domain(allowed_character_sets);

  // generate password
  char *pw = new char[length + 1];
  pw[length] = '\0'; // null terminate
  for (unsigned int c = 0; c < count; c++) {
    generate_password(pw, domain, domain_length, length);
    std::cout << pw << std::endl;
  }
  delete[] domain;
  delete[] pw;
  return 0;
}
