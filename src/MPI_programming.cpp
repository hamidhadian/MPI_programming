
#include <stdio.h>
#include <mpi.h>
#include <iostream>
#include <unistd.h>
#include <vector>

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <memory>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

using namespace std;

int main(int argc, char ** argv) {




    int rank, size;
    char name[80];
    int length;
    int number_students =4;
    int number_print_result =0;

    vector<string> vct_courses;
    vector<double> vct_numbers;


    int number_cources =5;
    int cnt_times =0;

    static int cnt_students =1;
    int rnd_student_number =0 ;

    vct_courses.push_back("Computer programming");
    vct_courses.push_back("Algorithms");
    vct_courses.push_back("Data structures");
    vct_courses.push_back("Computer architecture");
    vct_courses.push_back("mathematics");

    double average=0;



    MPI_Status status;

    MPI_Init(&argc, &argv); // note that argc and argv are passed




    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(name,&length);

   // printf(" MPI: processor %d of %d on %s\n", rank,size,name);



    number_cources = vct_courses.size();



   while (  cnt_students <= number_students )
  //  while (  true )

    {

		  //int number;
		  double number;
		  double input = 0;
		  if (rank == 0)
		  {



			  if ( cnt_times < number_cources )

			   {


				    if ( cnt_times ==0 && cnt_students ==1 ) /// in pegham baray bare aval faghat print mishavad
				    {
				     cout << std::endl;
				     cout << ":::::This program get numbers for 4 students from Input and calculate the average of numbers separately:::" << std::endl;
				     cout << std::endl;
				     srand (time(NULL));
				     rnd_student_number = rand() % 2000 + 1;
				    }




				  cout << "::process 1 :Please enter a number for student ::"<< rnd_student_number<< " :"<< vct_courses[cnt_times]+ "::\n>" ;

			 // getline(cin, input);
			  	  cin >> input;
			  	  number = input;

			  cnt_times++;
			  MPI_Send(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
			  //MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);


			   }else {



            	  //number = -5*cnt_students;  /// sending this number means end of transfer
            	  //MPI_Send(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);

            	  /// az in tarigh shomare daneshgo ra ba tag miferestim


            	  MPI_Send(&number, 1, MPI_DOUBLE, 1, rnd_student_number, MPI_COMM_WORLD);


            	  cnt_students++;
            	  cnt_times=0;
            	  sleep(1);
            	  srand (time(NULL));
            	  rnd_student_number = rand() % 2000 + 1;



            	 // break;

             }




		  }


		   if (rank == 1 )
		   {


			  // MPI_Recv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			   MPI_Recv(&number, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

               int tag_reeive=0;
               tag_reeive= status.MPI_TAG;




			   if ( number  >=0  ) vct_numbers.push_back(number);






			   if ( tag_reeive > 0) /// shomare daneshjoy ra daryaft mikonad
			   {


				 //  int tmp_student_number = -1 *  (number /5);

				   number_print_result++;


				   double tmp_average =0;

				   for (int i=0;i<vct_numbers.size();i++ )
				   {

					   tmp_average += vct_numbers[i];

				   }

				   tmp_average = tmp_average / vct_numbers.size();

				    cout << std::endl;


				   std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::"    << std::endl;
				   std::cout << "::process 2:::student number::"<< tag_reeive << "::FinalAverage of courses:::"<< tmp_average  << std::endl;
				   std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::"   << std::endl;
				   cout << std::endl;

				   vct_numbers.clear();

				   if ( number_print_result >= number_students  )
				   {
					   std::cout    << std::endl;
					   std::cout << ":::::::::::::::::::End of program::::::::::::::::::::"    << std::endl;
					   break;
				   }


			   }




		  }





    }  /// end of while




  //  std::cout << "::::::::::::exit one of the threads::::::::::::"   << std::endl;
    sleep(2);


//   int err= MPI_Abort(MPI_COMM_WORLD, 911);
//    exit(0);
     //MPI_Abort(MPI_COMM_WORLD, 1);

     MPI_Finalize();

return 0;

}



