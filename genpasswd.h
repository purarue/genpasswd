
#define GENPASSWD__IDENTIFIER
#ifndef GENPASSWD__IDENTIFIER

/**
 * Gets the environment variable 'envvar' as an integer
 * or defaults to 'def_val'
 */
int get_env_or(const std::string &envvar, unsigned int def_val);

/**
 * Tries to parse an unsigned int from 's' to 'length_arg'
 * If not parsable, does nothing
 */
void parse_int(std::optional<unsigned int> &length_arg, const char *s);

/**
 * Given the allowed_character_sets array (bool[4]),
 * generates the allow character domain
 */
const char *generate_domain(const bool *char_sets);

/**
 * Sets 'pw' to a password of length 'length', randomly picking from 'domain'
 */
void generate_password(char *pw, const std::string &domain,
                       unsigned int length);

#endif
