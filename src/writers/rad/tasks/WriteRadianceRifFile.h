/*****************************************************************************
 Emp
 
 Copyright (C) 2018  German Molina (germolinal@gmail.com)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 *****************************************************************************/
#pragma once

class WriteRadianceRifFile : public Task {
public:
    std::string filename; //!< The name of the file to write
    EmpModel * model; //!< The model to export
    OptionSet options;
    
    //! Constructor
    /*!
     @author German Molina
     @param[in] theFilename The file name
     @param[in] theModel The EmpModel object
     */
    WriteRadianceRifFile(std::string theFilename, EmpModel * theModel, OptionSet * theOptions)
    {
        std::string name = "Write RIF file";
        setName(&name);
        
        filename = theFilename;
        model = theModel;
        options = *theOptions;
    }
    
    //! Compares two of these tasks
    /*!
     @author German Molina
     @param[in] t The other ExportRadianceDir object
     @return are equal?
     */
    bool isEqual(Task * t)
    {
        return (
                model == static_cast<WriteRadianceRifFile *>(t)->model &&
                filename == static_cast<WriteRadianceRifFile *>(t)->filename
                );
    }
    
    //! Solves this task
    /*!
     @author German Molina
     @return success
     */
    bool solve()
    {
        RadExporter r = RadExporter(model);
        return r.writeRifFile(filename.c_str(), &options);
    }
    
    //! Is mutex
    /*!
     This method checks whether this Task is mutual exclusive with another Task;
     but it is never mutual excusive, so it returns false
     
     @author German Molina
     @param[in] t The other task
     @return true or false
     */
    bool isMutex(Task * t)
    {
        return false;
    }
    
    //! Submits the results into a json
    /*!
     This method checks whether this Task is mutual exclusive with another Task;
     but it is never mutual excusive, so it returns false
     
     @author German Molina
     @param[out] results The results json object
     @return true or false
     */
    bool submitResults(json * results)
    {
        return true;
    }
    
    
};

extern WriteRadianceRifFile writeRadianceRifFile;
