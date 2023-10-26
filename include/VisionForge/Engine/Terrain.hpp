/*
This class represents terrain class. It can create terrain from height map, generate a new one, edit and so on.
*/


#pragma once 

namespace vision{

    class ITerrain{
        public:
        ITerrain() = default;

        virtual ~ITerrain() = default;

        private:

    };

    ITerrain* CreateDefaultTerrain();

}