#include <stdio.h>
#include <string.h>

#define MAX 50

struct Employee {
    int empID;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    int joiningYear;
    char phone[15];
    char email[50];
};

void inputEmployee(struct Employee *e) {
    printf("Enter Employee ID: ");
    scanf("%d", &e->empID);

    printf("Enter name: ");
    scanf(" %[^\n]", e->name);

    printf("Enter department (IT/HR/Finance/Marketing/Operations): ");
    scanf(" %[^\n]", e->department);

    printf("Enter designation (Intern/Junior/Senior/Manager/Director): ");
    scanf(" %[^\n]", e->designation);

    printf("Enter salary: ");
    scanf("%f", &e->salary);

    printf("Enter joining year (YYYY): ");
    scanf("%d", &e->joiningYear);

    printf("Enter phone number: ");
    scanf(" %[^\n]", e->phone);

    printf("Enter email: ");
    scanf(" %[^\n]", e->email);
}
int experience(struct Employee e, int currentYear) {
    return currentYear - e.joiningYear;
}

void displayEmployee(struct Employee e, int currentYear) {
    printf("\nID: %d\nName: %s\nDepartment: %s\nDesignation: %s\nSalary: %.2f\nJoining Year: %d\nPhone: %s\nEmail: %s\nExperience: %d years\n",
           e.empID, e.name, e.department, e.designation, e.salary, e.joiningYear, e.phone, e.email, experience(e, currentYear));
}
void departmentSalaryStats(struct Employee employees[], int n) {
    char departments[5][20] = {"IT","HR","Finance","Marketing","Operations"};
    int i,j,count;
    float total;
    for(i=0;i<5;i++){
        total=0; count=0;
        for(j=0;j<n;j++){
            if(strcmp(employees[j].department,departments[i])==0){
                total+=employees[j].salary;
                count++;
            }
        }
        if(count>0)
            printf("Department %s: Total Salary=%.2f, Average Salary=%.2f\n",departments[i],total,total/count);
    }
}

void annualAppraisal(struct Employee employees[], int n) {
    int i, percent;
    for(i=0;i<n;i++){
        printf("Enter performance increment %% for %s: ", employees[i].name);
        scanf("%d",&percent);
        if(percent<5) percent=5;
        if(percent>15) percent=15;
        employees[i].salary += employees[i].salary*percent/100.0;
        printf("New salary: %.2f\n", employees[i].salary);
    }
}

void searchEmployees(struct Employee employees[], int n, int currentYear) {
    int choice,i;
    printf("\nSearch by: 1.Department 2.Designation 3.Experience: ");
    scanf("%d",&choice);
    if(choice==1){
        char dept[20]; printf("Enter department: "); scanf(" %[^\n]", dept);
        for(i=0;i<n;i++) if(strcmp(employees[i].department,dept)==0) displayEmployee(employees[i],currentYear);
    }
    else if(choice==2){
        char des[20]; printf("Enter designation: "); scanf(" %[^\n]", des);
        for(i=0;i<n;i++) if(strcmp(employees[i].designation,des)==0) displayEmployee(employees[i],currentYear);
    }
    else if(choice==3){
        int exp; printf("Enter minimum experience in years: "); scanf("%d",&exp);
        for(i=0;i<n;i++) if(experience(employees[i],currentYear)>=exp) displayEmployee(employees[i],currentYear);
    }
    else printf("Invalid choice.\n");
}

void promotionEligibility(struct Employee employees[], int n, int currentYear) {
    int i;
    printf("\nEmployees eligible for promotion (>3 years in role):\n");
    for(i=0;i<n;i++){
        if(experience(employees[i],currentYear)>3)
            printf("%s (ID %d) - %d years\n",employees[i].name,employees[i].empID,experience(employees[i],currentYear));
    }
}

int main(){
    struct Employee employees[MAX];
    int n,i,choice;
    int currentYear=2025;

    printf("Enter number of employees: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("\n--- Employee %d ---\n",i+1);
        inputEmployee(&employees[i]);
    }
    do{
        printf("\nMenu:\n1.Display All Employees\n2.Department Salary Stats\n3.Annual Appraisal\n4.Search Employees\n5.Promotion Eligibility\n6.Exit\nEnter choice: ");
        scanf("%d",&choice);
        if(choice==1){
            for(i=0;i<n;i++) displayEmployee(employees[i],currentYear);
        }
        else if(choice==2){
            departmentSalaryStats(employees,n);
        }
        else if(choice==3){
            annualAppraisal(employees,n);
        }
        else if(choice==4){
            searchEmployees(employees,n,currentYear);
        }
        else if(choice==5){
            promotionEligibility(employees,n,currentYear);
        }
        else if(choice==6){
            printf("Exiting program.\n");
        }
        else printf("Invalid choice.\n");
    }while(choice!=6);

    return 0;
}

