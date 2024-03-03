#pragma once


namespace DietProcessingUI {
    /* Command class
    *  Describes operations that all commands have to implement
    */
    class Command {
    public:
        virtual ~Command() {
        }
        virtual void Execute() const = 0;
    };

    /* DisplayTagsCommand class
    *  This class displays a list of the tags in the tags database
    */
    class CreateFoodType : public Command {

    private:

    public:
        CreateFoodType();
        void Execute() const override;
    };


}
