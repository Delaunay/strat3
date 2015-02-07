#ifndef STRAT3_DATAMANAGER_DATAMANAGERRISK_HEADER
#define STRAT3_DATAMANAGER_DATAMANAGERRISK_HEADER

/*! @brief DataManagerDisk offer similar functionality than DataManager.
 *  The only difference is that no matrix is loaded in memory until the user
 * ask for it. Only parts of the matrix can be loaded if specified. This can be useful for huge dataset
 * or if RAM space is limited
*/
class DataManagerDisk
{
    public:

    protected:
};

#endif
