echo "Deleting old images"

rm pgm_svd/*;

echo "Compiling image files";

java PGMProcessor pgm/apollonian_gasket.ascii.pgm;
java PGMProcessor pgm/baboon.ascii.pgm;
java PGMProcessor pgm/balloons.ascii.pgm;
java PGMProcessor pgm/barbara.ascii.pgm;
java PGMProcessor pgm/coins.ascii.pgm;
java PGMProcessor pgm/columns.ascii.pgm;
java PGMProcessor pgm/dragon.ascii.pgm;
java PGMProcessor pgm/small.pgm;

echo "Done";