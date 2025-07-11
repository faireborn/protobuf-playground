#include <google/protobuf/message_lite.h>

#include <fstream>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;

void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const tutorial::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_name()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case tutorial::Person::PHONE_TYPE_MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case tutorial::Person::PHONE_TYPE_HOME:
          cout << "  Home phone #: ";
          break;
        case tutorial::Person::PHONE_TYPE_WORK:
          cout << "  Work phone #: ";
          break;
        default:
          cout << "  #: ";
      }
      cout << phone_number.number() << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  tutorial::AddressBook addressbook;

  {
    fstream input(argv[1], ios::in | ios::binary);
    if (!addressbook.ParsePartialFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListPeople(addressbook);

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
