#include <string>

class Person {
	public:
		Person(std::string name);
		std::string getName();
	protected:
		std::string mName;
		int mAge;
};

class Professor : public Person {
	public:
		Professor(std::string name, std::string department);
		std::string getDepartment();
	private:
		int mSalary;
		std::string mDepartment;
};

class Student : public Person {
	public:
		Student(std::string name, std::string major);
		std::string getMajor();
		void setGPA(double gpa);
	protected:
		std::string mMajor;
	private:
		double mGpa;
};

class UscStudent : protected Student {
	public:
		UscStudent(std::string name, std::string major, double gpa);
		std::string getUscEmail();
		void printTranscript();
	private:
		int mUscID;
		std::string mUscEmail;
};