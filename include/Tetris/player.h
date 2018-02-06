#ifndef PLAYER_H
#define PLAYER_H

namespace Tetris {
    class Player
    {
        public:
            unsigned int getPoints() const;
            void setPoints(unsigned int value);
            void addPoints(unsigned int points);

            unsigned int getLevel() const;
            void setLevel(unsigned int value);
            void addLevels(unsigned int levels);

            void blockPlaced();
            void linesDeleted(unsigned int count);

        protected:
            unsigned int points = 0;
            unsigned int level = 1;
    };
}


#endif // PLAYER_H
