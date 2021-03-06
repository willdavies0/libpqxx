#include "../test_helpers.hxx"

namespace
{
void test_row()
{
  pqxx::connection conn;
  pqxx::work tx{conn};
  pqxx::result rows{tx.exec("SELECT 1, 2, 3")};
  pqxx::row r{rows[0]};
  PQXX_CHECK_EQUAL(r.size(), 3, "Unexpected row size.");
  PQXX_CHECK_EQUAL(r.at(0).as<int>(), 1, "Wrong value at index 0.");
  PQXX_CHECK(r.begin() != r.end(), "Broken row iteration.");
  PQXX_CHECK(r.begin() < r.end(), "Row begin does not precede end.");
  PQXX_CHECK(r.cbegin() == r.begin(), "Wrong cbegin.");
  PQXX_CHECK(r.cend() == r.end(), "Wrong cend.");
  PQXX_CHECK(r.rbegin() != r.rend(), "Broken reverse row iteration.");
  PQXX_CHECK(r.crbegin() == r.rbegin(), "Wrong crbegin.");
  PQXX_CHECK(r.crend() == r.rend(), "Wrong crend.");
  PQXX_CHECK_EQUAL(r.front().as<int>(), 1, "Wrong row front().");
  PQXX_CHECK_EQUAL(r.back().as<int>(), 3, "Wrong row back().");
}


PQXX_REGISTER_TEST(test_row);
} // namespace
