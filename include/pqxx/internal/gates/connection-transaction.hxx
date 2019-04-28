#include <pqxx/internal/callgate.hxx>

namespace pqxx
{
class connection_base;

namespace internal
{
namespace gate
{
class PQXX_PRIVATE connection_transaction : callgate<connection_base>
{
  friend class pqxx::transaction_base;

  connection_transaction(reference x) : super(x) {}

  result exec(const char query[], int retries)
	{ return home().exec(query, retries); }
  void register_transaction(transaction_base *t)
	{ home().register_transaction(t); }
  void unregister_transaction(transaction_base *t) noexcept
	{ home().unregister_transaction(t); }

  bool read_copy_line(std::string &line)
	{ return home().read_copy_line(line); }
  void write_copy_line(const std::string &line)
	{ home().write_copy_line(line); }
  void end_copy_write() { home().end_copy_write(); }

  std::string raw_get_var(const std::string &var)
	{ return home().raw_get_var(var); }
  void raw_set_var(const std::string &var, const std::string &value)
	{ home().raw_set_var(var, value); }
  void add_variables(const std::map<std::string, std::string> &vars)
	{ home().add_variables(vars); }

  result exec_prepared(
	const std::string &statement,
	const internal::params &args)
  {
    return home().exec_prepared(statement, args);
  }

  result exec_params(const std::string &query, const internal::params &args)
  {
    return home().exec_params(query, args);
  }

  bool prepared_exists(const std::string &statement) const
	{ return home().prepared_exists(statement); }

  void take_reactivation_avoidance(int counter)
	{ home().m_reactivation_avoidance.add(counter); }
};
} // namespace pqxx::internal::gate
} // namespace pqxx::internal
} // namespace pqxx
