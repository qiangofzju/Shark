//===========================================================================
/*!
 *  \brief Linear Regression Tutorial Sample Code
 *
 *  This file is part of the "Random Forest" tutorial.
 *  It requires some toy sample data that comes with the library.
 *
 *  \author K. N. Hansen
 *  \date 2012
 *
 *  <BR><HR>
 *  This file is part of Shark. This library is free software;
 *  you can redistribute it and/or modify it under the terms of the
 *  GNU General Public License as published by the Free Software
 *  Foundation; either version 3, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 */
//===========================================================================

#include <shark/Data/Csv.h>
#include <shark/Algorithms/Trainers/RFTrainer.h>

#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h>

#include <iostream> 

using namespace std; 
using namespace shark;


int main() {

    //*****************LOAD AND PREPARE DATA***********************//
	// read data
	ClassificationDataset data;
        //Optical digits
        import_csv(data, "data/C.csv", LAST_COLUMN, " ", "#");


	//Split the dataset into a training and a test dataset
	ClassificationDataset dataTest = splitAfterElement(data,311);

	cout << "Training set - number of data points: " << data.size()
		 << " number of classes: " << numberOfClasses(data)
		 << " input dimension: " << inputDimension(data) << endl;

	cout << "Test set - number of data points: " << dataTest.size()
		 << " number of classes: " << numberOfClasses(dataTest)
		 << " input dimension: " << inputDimension(dataTest) << endl;

    RFTrainer trainer;
    RFClassifier model;
    
    //Train the model
    trainer.train(model, data);

    // evaluate Random Forest classifier
    ZeroOneLoss<unsigned int, RealVector> loss;
    Data<RealVector> prediction = model(data.inputs());
    cout << "Random Forest on training set accuracy: " << 1. - loss.eval(data.labels(), prediction) << endl;

    prediction = model(dataTest.inputs());
    cout << "Random Forest on test set accuracy:     " << 1. - loss.eval(dataTest.labels(), prediction) << endl;

}