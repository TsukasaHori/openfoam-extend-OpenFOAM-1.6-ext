/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::bufferedAccumulator

Description

SourceFiles
    bufferedAccumulatorI.H
    bufferedAccumulator.C
    bufferedAccumulatorIO.C

\*---------------------------------------------------------------------------*/

#ifndef bufferedAccumulator_H
#define bufferedAccumulator_H

#include "Field.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

template<class Type>
class bufferedAccumulator;

template<class Type>
Ostream& operator<<
(
    Ostream&,
    const bufferedAccumulator<Type>&
);

/*---------------------------------------------------------------------------*\
                      Class bufferedAccumulator Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class bufferedAccumulator
:
    public List< Field<Type> >
{
    // Private data

        label averagesTaken_;

        List<label> bufferOffsets_;


    // Private Member Functions

        inline Field<Type>& accumulationBuffer();

        inline const Field<Type>& accumulationBuffer() const;

        void accumulateAndResetBuffer(const label b);


public:

    //- Component type
    typedef typename pTraits<Type>::cmptType cmptType;


    // Static data members

        static const char* const typeName;


    // Constructors

        //- Construct null
        bufferedAccumulator();

        //- Construct from components
        bufferedAccumulator
        (
            const label nBuffers,
            const label bufferLength,
            const label bufferingInterval
        );

        //- Construct as copy
        bufferedAccumulator(const bufferedAccumulator<Type>&);


    // Destructor

        ~bufferedAccumulator();


    // Member Functions

        label addToBuffers(const List<Type>& valuesToAdd);

        Field<Type> averaged() const;

        void resetAveraging();


        // Access

            inline label averagesTaken() const;

            inline label nBuffers() const;

            inline label bufferLength() const;

            inline const List<label>& bufferOffsets() const;


        // Edit

            void setSizes
            (
                const label nBuffers,
                const label bufferLength,
                const label bufferingInterval
            );


    // Member Operators

        void operator=(const bufferedAccumulator<Type>&);


    // IOstream Operators

        friend Ostream& operator<< <Type>
        (
            Ostream&,
            const bufferedAccumulator<Type>&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "bufferedAccumulatorI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "bufferedAccumulator.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
