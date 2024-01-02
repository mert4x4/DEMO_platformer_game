#include "pch.h"





TEST(BoundaryObstacleTest, test1)
{
    BoundaryObstacle obstacle(nullptr, 10.0f, 20.0f, 30, 40, 5.0f, 3.0f, 100.0f, 150.0f);

    
    obstacle.update(0.1f);

    
    EXPECT_FLOAT_EQ(obstacle.x, 10.5f);  
    EXPECT_FLOAT_EQ(obstacle.y, 20.3f); 
    EXPECT_FLOAT_EQ(obstacle.hspeed, 5.0f);  
    EXPECT_FLOAT_EQ(obstacle.vspeed, 3.0f);  
    while (obstacle.x < 100.0f) {
        obstacle.update(0.1f);
    }

  
    EXPECT_FLOAT_EQ(obstacle.hspeed, 5.0f);
}
TEST(EntityTest, test2) {
    
    Entity entity(nullptr, 10.0f, 20.0f, 30, 40);

    
    entity.update(0.1f);

   
    EXPECT_EQ(entity.rect.x, 10); 
    EXPECT_EQ(entity.rect.y, 20); 
    EXPECT_EQ(entity.rect.w, 30); 
    EXPECT_EQ(entity.rect.h, 40);     
}
TEST(PrizeTest, PlayerCollisionFunction) {
    Prize prize(nullptr, 10.0f, 20.0f, 30, 40);

    prize.update(0.1f);

    
    prize.playerCollission(0.1f);

    
    EXPECT_EQ(prize.x, 600);  
    EXPECT_EQ(prize.y, 70); 

    
}





