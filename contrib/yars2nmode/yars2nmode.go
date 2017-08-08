package main

import (
	"encoding/xml"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func main() {

	inputPtr := flag.String("input", "contrib/yars2nmode/svenja.xml", "RoSiML File")
	outputPtr := flag.String("output", "nmode.xml", "NMODE XML File")

	flag.Parse()

	if *inputPtr == "" {
		fmt.Println("Please given an input file name.")
		os.Exit(0)
	}

	fmt.Println("input file:  ", *inputPtr)
	fmt.Println("output file: ", *outputPtr)

	readXmlFile(inputPtr)

}

type XMLP3D struct {
	XMLName xml.Name `xml:"pose"`
	X       float64  `xml:"x,attr"`
	Y       float64  `xml:"y,attr"`
	Z       float64  `xml:"z,attr"`
}

func (p XMLP3D) String() string {
	return fmt.Sprintf("%f, %f, %f", p.X, p.Y, p.Z)
}

type XMLBox struct {
	XMLName xml.Name `xml:"box"`
	Name    string   `xml:"name,attr"`
	P3D     XMLP3D   `xml:"pose"`
}

type XMLSphere struct {
	XMLName xml.Name `xml:"sphere"`
	Name    string   `xml:"name,attr"`
	P3D     XMLP3D   `xml:"pose"`
}

type XMLCylinder struct {
	XMLName xml.Name `xml:"cylinder"`
	Name    string   `xml:"name,attr"`
	P3D     XMLP3D   `xml:"pose"`
}

type XMLPly struct {
	XMLName xml.Name `xml:"ply"`
	Name    string   `xml:"name,attr"`
	P3D     XMLP3D   `xml:"pose"`
}

type XMLComposite struct {
	XMLName xml.Name `xml:"composite"`
	Name    string   `xml:"name,attr"`
	P3D     XMLP3D   `xml:"pose"`
}

type XMLBody struct {
	XMLName    xml.Name       `xml:"body"`
	Boxes      []XMLBox       `xml:"box"`
	Spheres    []XMLSphere    `xml:"sphere"`
	Cylinders  []XMLCylinder  `xml:"cylinder"`
	Composites []XMLComposite `xml:"composites"`
	Plys       []XMLPly       `xml:"ply"`
}

type XMLSource struct {
	XMLName xml.Name `xml:"source"`
	Name    string   `xml:"name,attr"`
}

type XMLHinge struct {
	XMLName xml.Name  `xml:"hinge"`
	Name    string    `xml:"name,attr"`
	Source  XMLSource `xml:"source"`
	P3D     XMLP3D    `xml:"pose"`
}

type XMLSlider struct {
	XMLName xml.Name  `xml:"slider"`
	Name    string    `xml:"name,attr"`
	Source  XMLSource `xml:"source"`
	P3D     XMLP3D    `xml:"pose"`
}

type XMLGeneric struct {
	XMLName xml.Name  `xml:"generic"`
	Name    string    `xml:"name,attr"`
	Source  XMLSource `xml:"source"`
}

type XMLActuators struct {
	XMLName  xml.Name     `xml:"actuators"`
	Hinges   []XMLHinge   `xml:"hinge"`
	Sliders  []XMLSlider  `xml:"slider"`
	Generics []XMLGeneric `xml:"generic"`
}

type XMLRobot struct {
	XMLName   xml.Name     `xml:"robot"`
	Name      string       `xml:"name,attr"`
	Body      XMLBody      `xml:"body"`
	Actuators XMLActuators `xml:"actuators"`
	// Sensors   XMLSensors   `xml:"sensors"`
}

type XMLRobots struct {
	XMLName xml.Name   `xml:"robots"`
	Robots  []XMLRobot `xml:"robot"`
}

type XMLRoSiML struct {
	XMLName xml.Name  `xml:"rosiml"`
	Name    string    `xml:"key,attr"`
	Robots  XMLRobots `xml:"robots"`
}

func ReadRobot(reader io.Reader) (*XMLRobot, error) {
	var xmlRoSiML XMLRoSiML
	if err := xml.NewDecoder(reader).Decode(&xmlRoSiML); err != nil {
		return nil, err
	}

	return &(xmlRoSiML.Robots.Robots[0]), nil
}

func readXmlFile(filename *string) {

	filePath, err := filepath.Abs(*filename)

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	file, err := os.Open(filePath)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	defer file.Close()

	xmlRobot, err := ReadRobot(file)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	fmt.Printf("Robot Name: %s\n", (*xmlRobot).Name)

	for _, sphere := range (*xmlRobot).Body.Spheres {
		fmt.Printf("Sphere Name: %s\n", sphere.Name)
		fmt.Printf("  %s\n", sphere.P3D)
	}

	for _, box := range (*xmlRobot).Body.Boxes {
		fmt.Printf("Box Name: %s\n", box.Name)
		fmt.Printf("  %s\n", box.P3D)
	}

	for _, composite := range (*xmlRobot).Body.Composites {
		fmt.Printf("Composite Name: %s\n", composite.Name)
		fmt.Printf("  %s\n", composite.P3D)
	}

	for _, ply := range (*xmlRobot).Body.Plys {
		fmt.Printf("Ply Name: %s\n", ply.Name)
		fmt.Printf("  %s\n", ply.P3D)
	}

}
