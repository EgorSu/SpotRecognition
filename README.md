# SpotRecognition
In this project, the parameters of the two-dimensional normal distribution over the image are measured. For this, histograms of pixel intensities were calculated as the sum of pixel intensities along the axis x and y. Histograms are also calculated for an image rotated by 45 degrees to determine the rotation of the normal distribution. Since the values on the histograms also have a normal distribution, then we define the standard deviation of these values through FWHM as σ = FWHM/2.355. Thus, from the four obtained values of the standard deviation (2 for the initial image and two for the rotated image), we can calculate the standard deviation and the angle of rotation for the two-dimensional distribution. We can also calculate the expected value from expected values of two one-dimensional distributions.   
The project was done in C++ using Qt and the computer vision library OpenCV. The GUI was created with using Qt Designer.
